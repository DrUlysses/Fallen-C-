extends Area2D

var speed = 1
var pos = get_pos()

func _process(delta):
	pos += Vector2(0, - (delta * speed))
	set_pos(pos)

func _ready():
	set_process(true)
	
func _on_visibility_exit_screen():
	queue_free()
