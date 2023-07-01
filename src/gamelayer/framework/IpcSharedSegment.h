#ifndef IPC_SHAREDSEGMENT_H
#define IPC_SHAREDSEGMENT_H

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>

using namespace boost::interprocess;

template <typename T> class IpcSharedSegment {
public:
  typedef allocator<T, managed_shared_memory::segment_manager> ShmemAllocator;
  typedef std::vector<T, ShmemAllocator> SharedVector;

  struct shm_remove {
    std::string segmentStr;
    shm_remove(std::string segment) {
      segmentStr = segment;
      shared_memory_object::remove(segment.c_str());
    }
    ~shm_remove() { shared_memory_object::remove(segmentStr.c_str()); }
  }; // remover;

  IpcSharedSegment(std::string nameSegment, int allocSize = 4096) {
    // Create a new segment with given name and size
    remover = new shm_remove(nameSegment);
    segment =
        managed_shared_memory(create_only, nameSegment.c_str(), allocSize);

    // Initialize shared memory STL-compatible allocator
    // const ShmemAllocator alloc_inst (segment.get_segment_manager());
  }

  ~IpcSharedSegment() {
      if (remover)
          delete remover;
    }

  bool allocateVectorArray(std::string nameArray, int elementCount = -1) {
    bool res = false;
    std::lock_guard<std::mutex> guard(myMutex);
    const ShmemAllocator alloc_inst(segment.get_segment_manager());
    // Construct a vector named <nameArray> in shared memory with argument
    // alloc_inst
    SharedVector *myvector = segment.construct<SharedVector>(nameArray.c_str())(alloc_inst);
    if (myvector != nullptr && elementCount > 0)
      myvector->reserve(elementCount);
    if (myvector != nullptr)
      mapSharedVectors[nameArray] = myvector;
    res = myvector != nullptr;
    return res;
  }

  bool allocateVectorArray(std::string nameArray, vector<T> &fromArray,
                           int elementCount = -1) {
    bool res = false;
    std::lock_guard<std::mutex> guard(myMutex);
    const ShmemAllocator alloc_inst(segment.get_segment_manager());
    // Construct a vector named "MyVector" in shared memory with argument
    // alloc_inst
    SharedVector *myvector =
        segment.construct<SharedVector>(nameArray.c_str())(alloc_inst);
    if (myvector != nullptr && elementCount > 0)
      myvector->reserve(elementCount);
    if (myvector != nullptr)
      mapSharedVectors[nameArray] = myvector;
    res = myvector != nullptr;
    for (T item : fromArray) {
      myvector->push_back(item);
    }
    return res;
  }

  std::optional<SharedVector *> getVectorArray(std::string nameArray) {
    std::optional<SharedVector *> res = std::nullopt;
    std::lock_guard<std::mutex> guard(myMutex);
    auto it = mapSharedVectors.find(nameArray);
    if (it != mapSharedVectors.end()) {
      res = std::make_optional(it->second);
    }
    return res;
  }

  bool existsVectorArray(std::string nameArray) {
    bool res = false;
    std::lock_guard<std::mutex> guard(myMutex);
    auto it = mapSharedVectors.find(nameArray);
    res = (it != mapSharedVectors.end());
    return res;
  }

  int vectorArraySize(std::string nameArray) {
    int res = 0;
    std::lock_guard<std::mutex> guard(myMutex);
    auto it = mapSharedVectors.find(nameArray);
    if (it != mapSharedVectors.end()) {
      SharedVector *sharedVectorComp = it->second;
      if (sharedVectorComp != nullptr)
      {
        res = sharedVectorComp->size();
      }
    }
    return res;
  }

  bool vectorArrayAdd(std::string nameArray, T element) {
    bool res = false;
    std::lock_guard<std::mutex> guard(myMutex);
    auto it = mapSharedVectors.find(nameArray);
    if (it != mapSharedVectors.end()) {
      SharedVector *sharedVectorComp = it->second;
      if (sharedVectorComp != nullptr)
      {
        sharedVectorComp->push_back(element);
        res = true;
      }
    }
    return res;
  }

  bool vectorArrayRemove(std::string nameArray, T element) {
    bool res = false;
    std::lock_guard<std::mutex> guard(myMutex);
    auto it = mapSharedVectors.find(nameArray);
    if (it != mapSharedVectors.end()) {
      SharedVector *sharedVectorComp = it->second;
      if (sharedVectorComp != nullptr)
      {
        sharedVectorComp->remove(element);
        res = true;
      }
    }
    return res;
  }

  bool vectorArrayContains(std::string nameArray, /*std::string*/T value) {
    bool res = false;
    std::lock_guard<std::mutex> guard(myMutex);
    auto it = mapSharedVectors.find(nameArray);
    if (it != mapSharedVectors.end()) {
      SharedVector *sharedVectorComp = it->second;
      if (sharedVectorComp != nullptr)
      {
        for (T item : *sharedVectorComp)
        {
          if (item == value)
          {
            res = true;
            break;
          }
        }
      }
    }
    return res;
  }

  T vectorPopValue(std::string nameArray) {
    T res;
    std::lock_guard<std::mutex> guard(myMutex);
    auto it = mapSharedVectors.find(nameArray);
    if (it != mapSharedVectors.end()) {
      SharedVector *sharedVectorComp = it->second;
      if ( (sharedVectorComp != nullptr) && (sharedVectorComp->size() > 0) )
      {
        //res = sharedVectorComp->pop_back();
        res = (*sharedVectorComp)[sharedVectorComp->size() - 1];
        sharedVectorComp->erase(sharedVectorComp->end() - 1);
      }
    }
    return res;
  }

private:
  managed_shared_memory segment;
  std::map<std::string, SharedVector *> mapSharedVectors;
  shm_remove* remover = nullptr;

  std::mutex myMutex;
};

#endif
