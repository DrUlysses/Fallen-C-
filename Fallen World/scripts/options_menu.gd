extends Control

func _on_fullscreen_toggled( pressed ):
	OS.set_window_fullscreen( pressed )
	get_node("fullscreen").set_disabled( !pressed )

func _on_back_pressed():
	get_tree().change_scene("res://main_menu.tscn")
