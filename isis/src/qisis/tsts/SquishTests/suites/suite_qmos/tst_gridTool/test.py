import os                                                                                               
import shutil                                                                                           
      
def main():
    # Backup current qmos settings                                                                     
    try:                                                                                                
        shutil.rmtree(os.path.expandvars('$HOME/.Isis/qmos.squishbackup'))                             
    except Exception:                                                                                   
        pass                                                                                            
                                                                                                        
    try:                                                                                                
        os.rename(os.path.expandvars('$HOME/.Isis/qmos'), os.path.expandvars('$HOME/.Isis/qmos.squishbackup'))
    except Exception:                                                                                   
        pass
    
    startApplication("qmos")
    activateItem(waitForObjectItem(":qmos_QMenuBar", "File"))
    activateItem(waitForObjectItem(":qmos.File_QMenu", "Open Cube..."))
    snooze(0.5)
    type(waitForObject(":fileNameEdit_QLineEdit"), "../src/qisis/tsts/SquishTests/input/lub2675j.342.lev1.cub")
    type(waitForObject(":_QListView"), "<Return>")

    snooze(3)
    
    # Change the projection to orthographic
    clickButton(waitForObject(":qmos.View/Edit Equirectangular Projection_QToolButton"))
    mouseClick(waitForObject(":Save Map File..._QTextEdit"), 3, 9, 0, Qt.LeftButton)
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Shift+End>")
    type(waitForObject(":Save Map File..._QTextEdit"), "Orthographic")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Down>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Right>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Del>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Del>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Del>")
    type(waitForObject(":Save Map File..._QTextEdit"), "157.9")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Left>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Up>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Up>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Up>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Up>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Up>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Up>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Del>")
    type(waitForObject(":Save Map File..._QTextEdit"), "<Del>")
    type(waitForObject(":Save Map File..._QTextEdit"), "18")
    clickButton(waitForObject(":Ok_QPushButton"))
    
    clickButton(waitForObject(":qmos_GridToolButton"))
    clickButton(waitForObject(":Latitude Extent Failure.OK_QPushButton"))
    clickButton(waitForObject(":Longitude Extent Failure.OK_QPushButton"))
    clickButton(waitForObject(":qmos.Grid Options_QPushButton"))


    clickButton(waitForObject(":Auto Grid_QCheckBox"))
    mouseClick(waitForObject(":Grid Options.Latitude Range_QComboBox"), 127, 3, 0, Qt.LeftButton)
    mouseClick(waitForObjectItem(":Grid Options.Latitude Range_QComboBox", "Manual"), 53, 3, 0, Qt.LeftButton)
    mouseDrag(waitForObject(":Grid Options_QLineEdit"), 77, 10, -92, -5, 1, Qt.LeftButton)
    type(waitForObject(":Grid Options_QLineEdit"), "0")
    mouseDrag(waitForObject(":Grid Options_QLineEdit_2"), 73, 1, -101, 2, 1, Qt.LeftButton)
    type(waitForObject(":Grid Options_QLineEdit_2"), "2")
    mouseClick(waitForObject(":Grid Options.Longitude Range_QComboBox"), 126, 7, 0, Qt.LeftButton)
    mouseClick(waitForObjectItem(":Grid Options.Longitude Range_QComboBox", "Manual"), 67, 1, 0, Qt.LeftButton)
    mouseDrag(waitForObject(":Grid Options_QLineEdit_3"), 76, 10, -90, -7, 1, Qt.LeftButton)
    mouseDrag(waitForObject(":Grid Options_QLineEdit_3"), 74, 6, -74, 2, 1, Qt.LeftButton)
    type(waitForObject(":Grid Options_QLineEdit_3"), "-113")
    mouseDrag(waitForObject(":Grid Options_QLineEdit_4"), 65, 7, -67, -1, 1, Qt.LeftButton)
    # This froze for mantis ticket #1060 - we're just checking that qmos doesn't lock up.
    type(waitForObject(":Grid Options_QLineEdit_4"), "-110")
    
    # Verify sliders are accurate (part of #1392)
    waitFor("object.exists(':Grid Options.Minimum Longitude_QSlider')", 20000)
    test.compare(findObject(":Grid Options.Minimum Longitude_QSlider").value, -113)
    test.compare(findObject(":Grid Options.Minimum Longitude_QSlider").minimum, -180)
    test.compare(findObject(":Grid Options.Minimum Longitude_QSlider").maximum, 180)
    clickButton(waitForObject(":Grid Options.Ok_QPushButton"))                                                           

    activateItem(waitForObjectItem(":qmos_QMenuBar", "View"))
    activateItem(waitForObjectItem(":_QMenu", "Hide Outline Column"))
    activateItem(waitForObjectItem(":qmos_QMenuBar", "View"))
    activateItem(waitForObjectItem(":_QMenu", "Hide Footprint Column"))
    activateItem(waitForObjectItem(":qmos_QMenuBar", "Settings"))
    activateItem(waitForObjectItem(":_QMenu", "Set Current File List Columns as Default"))
    snooze(1)   

    sendEvent("QCloseEvent", waitForObject(":qmos_Isis::MosaicMainWindow"))

                                                                           
    snooze(1)                        
    
    startApplication("qmos")
    activateItem(waitForObjectItem(":qmos_QMenuBar", "File"))
    activateItem(waitForObjectItem(":qmos.File_QMenu", "Open Cube..."))
    snooze(0.5)
    type(waitForObject(":fileNameEdit_QLineEdit"), "../src/qisis/tsts/SquishTests/input/lub2675j.342.lev1.cub")
    type(waitForObject(":_QListView"), "<Return>")

    snooze(3)
    
    # Test remembered column view states
    waitFor("object.exists(':View.Show Footprint Column_QAction')", 20000)
    test.compare(findObject(":View.Show Footprint Column_QAction").visible, True)
    test.compare(findObject(":View.Show Footprint Column_QAction").iconText, "Show Footprint Column")
    waitFor("object.exists(':View.Show Outline Column_QAction')", 20000)

    test.compare(findObject(":View.Show Outline Column_QAction").iconText, "Show Outline Column")
    test.compare(findObject(":View.Show Outline Column_QAction").visible, True)
    clickButton(waitForObject(":qmos_GridToolButton"))                                      
    snooze(1)   

    # Test remembered auto grid state
    waitFor("object.exists(':qmos.Auto Grid_QCheckBox')", 20000)
    test.compare(findObject(":qmos.Auto Grid_QCheckBox").checked, False)
    test.compare(findObject(":qmos.Auto Grid_QCheckBox").enabled, True)
    sendEvent("QCloseEvent", waitForObject(":qmos_Isis::MosaicMainWindow"))

                                                                           
    snooze(1)                        
         
    # Restore original qmos settings                                                                   
    try:                                                                                                
        shutil.rmtree(os.path.expandvars('$HOME/.Isis/qmos'))                                          
    except Exception:                                                                                   
        pass                                                                                            
                                                                                                        
    try:                                                                                                
        os.rename(os.path.expandvars('$HOME/.Isis/qmos.squishbackup'), os.path.expandvars('$HOME/.Isis/qmos'))
    except Exception:                                                                                   
        pass                                                                                            
             