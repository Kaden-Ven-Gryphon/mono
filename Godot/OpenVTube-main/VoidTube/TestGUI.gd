extends Node




func _on_TogleTracking_pressed():
	$"2dcharactertuber/meshcontroler".togle_tracking()


func _on_TogleMesh_pressed():
	$"2dcharactertuber/meshcontroler".togle_mesh()


func _on_Button_pressed():
	$"2dcharactertuber/meshcontroler".shut_down_server()
