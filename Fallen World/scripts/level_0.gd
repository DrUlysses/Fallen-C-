extends Node2D
#		# Just pressed
#		var shot = preload("res://bullet_0.tscn").instance()
#		# Use the Position2D as reference
#		shot.set_pos(get_node("shootfrom").get_global_pos())
#		# Put it two parents above, so it is not moved by us
#		get_node("../..").add_child(shot)
func _ready():