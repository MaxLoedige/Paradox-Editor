extends Control

var currentActive :int = 1
var parent : HSplitContainer = null

@onready var FileMenu : Control = $FileMenu
@onready var LocMenu : Control = $LocMenu
@onready var GraphMenu : Control = $GraphMenu

var threshold = 80
var active = true
var last_offset = threshold + 20

func _process(delta):
	
	if parent == null:
		parent = get_parent()
	
	if not active and parent.split_offset > 0:
		parent.split_offset = threshold + 20
		active = true
		last_offset = threshold + 20
		print("setting last Threshold 1 ", last_offset)
		_change()
		
	if active and parent.split_offset < threshold - 20:
		parent.split_offset = 0
		active = false
		last_offset = threshold + 20
		print("setting last Threshold 2 ", last_offset)
		_change()
	#print(parent.split_offset, currentActive, invis)
	#if parent.split_offset <= threshold and not invis:
		#parent.split_offset
		#_change()
	#elif parent.split_offset > threshold:
		#invis = false
		#_change()

func _change():
	FileMenu.visible = false
	LocMenu.visible = false
	GraphMenu.visible = false

	if not active:
		return

	if currentActive == 1:
		FileMenu.visible = true
	elif currentActive == 2:
		LocMenu.visible = true
	elif currentActive == 3:
		GraphMenu.visible = true

func _on_Btn(id:int):
	var tmp = parent.split_offset
	if currentActive == id:
		currentActive = 0
		active = false
		parent.split_offset = 0
		last_offset = tmp
	else:
		currentActive = id
		if not active and last_offset <= threshold:
			parent.split_offset = threshold + 20
		elif not active:
			parent.split_offset = last_offset
		active = true
	_change()

func _on_FilesBtn_up():
	_on_Btn(1)
	
func _on_LocBtn_up():
	_on_Btn(2)
	
func _on_GraphBtn_up():
	_on_Btn(3)


func _on_f_button_pressed():
	print("Test File")


func _on_l_button_pressed():
	print("Test Loc")
