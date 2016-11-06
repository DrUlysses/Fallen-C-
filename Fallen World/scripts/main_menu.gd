extends Control

func _on_new_game_pressed():
	get_tree().change_scene("res://new_game_menu.tscn")

func _on_exit_pressed():
	get_tree().quit()

func _on_options_pressed():
	get_tree().change_scene("res://options_menu.tscn")
