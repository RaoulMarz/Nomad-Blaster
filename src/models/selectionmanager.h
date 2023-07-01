#ifndef SELECTIONMANAGER_CLASS_H
#define SELECTIONMANAGER_CLASS_H

#include "infowrapper.h"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <iostream>
#include <vector>

template <typename T>
class SelectionManager {
private:
	//List<InfoWrapper<T>> items = new List<InfoWrapper<T>>();
	std::unique_ptr<std::vector<InfoWrapper<T>>> items = std::make_unique<std::vector<InfoWrapper<T>>>();
	int activeIndex = 0;

public:
	int size() {
		return items->size();
	}

	InfoWrapper<T> get(int i) {
		if ((items == nullptr) || (items->size() <= i))
			return nullptr;
		return items[i];
	}

	int getActiveIndex() {
		return activeIndex;
	}

	void setActive(int i) {
		if (i < 0 || i >= items->size()) {
			//throw new Exception($"selection index = {i} out of bounds (size is {items.Count})");
		}

		if (i != activeIndex) {
			activeIndex = i;
			//ActiveChanged();
		}
	}

	std::optional<InfoWrapper<T>> getActive() {
		if (items->size() <= activeIndex)
			return std::nullopt;
		return (*items)[activeIndex];
	}

	void add(InfoWrapper<T> item) {
		bool wasEmpty = size() == 0;
		items->push_back(item);

		if (wasEmpty) {
			//activeChanged();
		}
	}

	void addAll(std::vector<InfoWrapper<T>> itemsList) {
		bool wasEmpty = size() == 0;
		//this.items.AddRange(items);
		//items = std::vector<InfoWrapper<T>>(itemsList);
		copy(itemsList.begin(), itemsList.end(), std::back_inserter(*items));

		if (wasEmpty) {
			//activeChanged();
		}
	}

	bool contains(InfoWrapper<T> item) {
		bool res = false;
		return res; //items.Contains(item);
	}

	/**
	 * Returns whether there exists an item whose name is equal to the given string.
	 */
	bool hasName(std::string name) {
		return getIndexByName(name) != -1;
	}

	int getIndexByName(std::string name) {
		int i = 0;
		for (InfoWrapper<T> item : items) {
			if (name == item.name) {
				return i;
			}
			i++;
		}
		return -1;
	}

	//template <typename T>
	friend std::ostream &operator<<(std::ostream &outs, SelectionManager<T> &p) {
		return outs << "<SelectionManager>"; /*<< p.getFlavour() << ")"*/
	}

	//template <typename T>
	friend std::string to_string(const SelectionManager<T> &value) {
		std::ostringstream ss;
		ss << value;
		return ss.str();
	}

	operator std::string() const {
		std::ostringstream out;
		out << *this;
		return out.str();
	}
};

#endif