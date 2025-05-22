@tool
extends Control

@export var overridePath : String = ""
var dir : DirAccess

func _ready():
	populate()
	
func populate():
	if not overridePath.is_empty() and DirAccess.dir_exists_absolute(overridePath):
		dir = DirAccess.open(overridePath)
		
