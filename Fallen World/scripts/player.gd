extends Area2D

var speed = 10
var live = true
var pos = Vector2()

func _ready():
	set_fixed_process(true)
	pos = get_pos()

func _fixed_process(delta):
	var move = Vector2(0, 0)
	
	if Input.is_action_pressed("ui_up"):
		move += Vector2(0, -1)
	
	if Input.is_action_pressed("ui_left"):
		move += Vector2(-1, 0)
		
	if Input.is_action_pressed("ui_down"):
		move += Vector2(0, 1)
		
	if Input.is_action_pressed("ui_right"):
		move += Vector2(1, 0)
	
	move *= speed
	pos += move
	set_pos(pos)
	print(get_node("tick").get_wait_time())
	if (Input.is_action_pressed("shoot") and get_node("tick").get_wait_time() == 1):
		var shot = preload("res://bullet_0.tscn").instance()
		shot.set_pos(get_node("gun").get_global_pos())
		get_parent().add_child(shot)
		get_node("tick").start()


#var prev_shooting = false
#var killed = false
#
#func _ready():
#	#сделать появление в нижней части экрана без магических чисел
#	var pos = Vector2(OS.get_window_size().width/2, OS.get_window_size().height - 43)
#	set_pos(pos)
#
#func _fixed_process(delta):
#	var motion = Vector2()
#	if Input.is_action_pressed("move_up"):
#		motion += Vector2(0, -1)
#	if Input.is_action_pressed("move_down"):
#		motion += Vector2(0, 1)
#	if Input.is_action_pressed("move_left"):
#		motion += Vector2(-1, 0)
#	if Input.is_action_pressed("move_right"):
#		motion += Vector2(1, 0)
#	var shooting = Input.is_action_pressed("shoot")
#	
#	var pos = get_pos()
#	
#	pos += motion*delta*speed
#	if (pos.x < 0):
#		pos.x = 0
#	if (pos.x > screen_size.x):
#		pos.x = screen_size.x
#	if (pos.y < 0):
#		pos.y = 0
#	if (pos.y > screen_size.y):
#		pos.y = screen_size.y
#	
#	set_pos(pos)
#	
#	if (shooting and not prev_shooting):
#		# Just pressed
#		var shot = preload("res://bullet_0.tscn").instance()
#		# Use the Position2D as reference
#		shot.set_pos(get_node("shootfrom").get_global_pos())
#		# Put it two parents above, so it is not moved by us
#		get_node("../..").add_child(shot)
#	
#	prev_shooting = shooting
#
#func _hit_something():
#	if (killed):
#		return
#	killed = true
#	get_node("anim").play("explode")
#	get_node("../hud/game_over").show()
#	get_node("/root/game_state").game_over()
#	get_parent().stop()
#	set_process(false)
#
#func _on_player_body_enter(body):
#	_hit_something()
#
#func _on_back_to_menu_pressed():
#	get_tree().change_scene("res://main_menu.tscn")
#
#func _on_player_area_enter( area ):
#	if (area.has_method("is_enemy") and area.is_enemy()):
#		_hit_something() 