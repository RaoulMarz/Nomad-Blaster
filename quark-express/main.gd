extends Node2D

@onready var particlesPlay : ParticlesPalace = $ParticlesPalace
@onready var nomadDisplayer : NomadDisplay = $NomadDisplay
@onready var imageRapRip : ImageRipper = $ImageRipper

# Called when the node enters the scene tree for the first time.
func _ready():
	imageRapRip.set_size(Vector2(256, 256))
	imageRapRip.create_noise_image_textparam("perlin_fractal", 1193, 0.02, 4)
	#ImageRipper.PERLINFRACTAL_NOISE
	var img_data = imageRapRip.get_data()
	#prints("  $ImageRipper [data] --> ", img_data)
	var img_pixels = imageRapRip.get_pixels_raw()
	prints("  $ImageRipper [raw pixels] --> ", img_pixels)
	nomadDisplayer.set_working_path("/media/Spacehub/home/Shared/Projects/2023-CyFi/Bots/Work")
	nomadDisplayer.set_size(Vector2(1020, 840))
	nomadDisplayer.set_dimensions("game", Vector2(20, 20), Vector2(820, 640))
	#particlesPlay.setup()
	
	#particlesPlay.enable_debug(true)
	#particlesPlay.set_physical_parameters(3, 12)
	#particlesPlay.set_timesync_enabled(true)
	#particlesPlay.set_extended_draw(true)
	particlesPlay.visible = true

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#particlesPlay.queue_redraw()
	pass

func _input(event):
	#var current_time = timestamp_class.timestamp.new()
	#current_time.reset_time()
	#var ticksElapsed = current_time.subtract_ticks(time_tool_dirpressed)
	if !event is InputEventKey:
		pass
	#screen_size = get_viewport().size
	var exitKey = Input.is_action_pressed("exit")
	if (exitKey):
		get_tree().quit()

