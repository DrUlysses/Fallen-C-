extends Control

func _on_back_pressed():
	get_tree().change_scene("res://main_menu.tscn")


func _on_play_pressed():
	get_tree().change_scene("res://level_0.tscn")
