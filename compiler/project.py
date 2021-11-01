from devkit_tools import Project 
from doltools import write_lis, write_ori


def patch_osarena_low(dol, size):
    #800eb370
    dol.seek(0x804a16bc) # OSinit before calling OSSetarenalo
    write_lis(dol, 3, size >> 16, signed=False)
    write_ori(dol, 3, 3, size & 0xFFFF)
    
    dol.seek(0x804a1670) # also OSInit 
    write_lis(dol, 3, size >> 16, signed=False) 
    write_ori(dol, 3, 3, size & 0xFFFF)
    
    print("New size", hex(size))

p = Project("mario.dol", address=0x806bdfa0) # actually smaller
p.set_osarena_patcher(patch_osarena_low)

p.add_file("../source/main.c")
p.add_linker_file("../galaxySymbols.txt")
p.apply_gecko("extraCode.txt")

p.branchlink(0x8033e820, "beforeDrawAll3D")
p.branchlink(0x8033ef68, "beforeDrawShadowStuff")
#p.branchlink(0x8033ef6c, "beforeDrawShadowStuff")
#fixes shadows
#p.branchlink(0x803cb374, "editMtxOrtho")
#p.branchlink(0x803cabd0, "editMtxOrtho")
p.branch(0x804b6a58, "editMtxOrtho")
#fixes melty splatter galaxy
p.branchlink(0x80363e18, "editMtxOrtho")
p.branchlink(0x80345050, "allocateCameras")
p.branch(0x8009b08c, "getCameraNew")
p.branch(0x804be45c, "storeFloatFuncNew")
#p.branchlink(0x8033eefc, "storeFloatFuncNew")
#p.branchlink(0x80313bf8, "storeFloatFuncNew")
p.branchlink(0x802aeda0, "beforeMarioCreation")
p.branch(0x802af3f8, "afterMarioCreation")
p.branchlink(0x802afdd4, "onStartMarioUpdate")
p.branchlink(0x802b0750, "onEndMarioUpdate")
p.branchlink(0x80343c1c, "updateMarioManager")
p.branch(0x803cc588, "isLuigiNew")
p.branchlink(0x802aeda0, "toggleWeegeeMode")
p.branchlink(0x802b2a40, "onStartMarioAlternativeUpdate")
p.branchlink(0x80343bf4, "updateStuffManager")
p.branchlink(0x801654fc, "checkCollidedObjectNew")
p.branchlink(0x801d1b88, "onMarioTouchPipe")
p.branchlink(0x8024640c, "onMarioTouchesStar")
p.branch(0x80165fc8, "onMarioTouchesStar") # for mini stars
p.branch(0x8033cc30, "onMarioTouchesSwing") 
p.branchlink(0x80343b34, "updateCameraManager")
p.branchlink(0x800991e4, "checkCameraFirstFunc")
p.branch(0x800a27ec, "getMainCamerasThingy")
p.branchlink(0x800a29ac, "getMainCamerasThingy")
p.branchlink(0x8033e684, "fixBothCameras")
p.branchlink(0x802c8bfc, "onMarioTouchesObject")
p.branchlink(0x8033ef30, "beforeDrawDrip")
p.branchlink(0x8015ef9c, "makeCullingWork")
p.branchlink(0x80346a4c, "makeBothMarios")
#p.branch(0x803671c8, "drawCustom2D") good place but also defunct because is ran multiple times which = dumb
p.branch(0x80344454, "drawCustom2D")
p.branchlink(0x803ca670, "beforeSetScissor")
p.branchlink(0x803bd3d4, "calcMarioDistanceNew")
p.branchlink(0x802c548c, "beforeMarioKick")
p.branchlink(0x80344234, "beforeDrawShadowMario")
p.branchlink(0x8001ef08, "beforeAstroDomeVolumeCheck")
p.branchlink(0x80241748, "giveMarioPos")
#allow both marios to die to void/death planes
p.branch(0x80021f00, "deathBarrierCheckNew")


#PAL ADDRESSES are same
p.branchlink(0x8009966c, "firstPersonControlsOverhaul")
p.branchlink(0x80099240, "beforeFirstPerson")
p.branch(0x800998d8, "firstPersonEnd") 
#p.branchlink(0x802eb1a4, "setMarioRotation")
p.branchlink(0x802eaef4, "setMarioRotation")
p.branchlink(0x802eb1a4, "setMarioVelocity")
p.branchlink(0x802b0854, "beforeMovement")
p.branch(0x802ab5b8, "mRotateNew")
p.branchlink(0x800aee48, "forceFirstCamRot")

#p.build_gecko(0x800044c0, "gecko.txt")

#gxsetscissor 804be4b0


p.build("C:\\Max's folder\\Folder Games\\super mario galaxy\\DATA\\sys\\main.dol")
