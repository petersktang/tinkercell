SET(LIBRARY_OUTPUT_PATH ${CPP_LIBRARY_OUTPUT_PATH})

INCLUDE_DIRECTORIES( BEFORE
    ${TINKERCELL_SOURCE_DIR}/BasicTools
    ${TINKERCELL_SOURCE_DIR}/NodesTree
 )

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

SET( TINKERCELL_CORE_HDRS
  ../Core/MainWindow.h 
  ../Core/NetworkHandle.h
  ../Core/NetworkWindow.h
  ../Core/CodeEditor.h
  ../Core/TextEditor.h 
  ../Core/GraphicsScene.h
  ../Core/GraphicsView.h  
  ../Core/Tool.h
  )

CONFIGURE_FILE( TinkerCellAboutBox.cpp.in
  ${TINKERCELL_BINARY_DIR}/BasicTools/TinkerCellAboutBox.cpp
  @ONLY
)

QT4_ADD_RESOURCES( TINKERCELL_BASICTOOLS_QRC ../Core/Tinkercell.qrc )

SET(TINKERCELL_BASICTOOLS_SRC 
  ${TINKERCELL_BINARY_DIR}/BasicTools/TinkerCellAboutBox.cpp
  CollisionDetection.cpp
  ConnectionInsertion.cpp
  ConnectionMaker.cpp
  ConnectionSelection.cpp
  DnaGraphicsItem.cpp
  GraphicsReplaceTool.cpp
  GraphicsTransformTool.cpp
  GroupHandlerTool.cpp
  NameFamilyDialog.cpp
  NodeInsertion.cpp
  NodeSelection.cpp
  BasicToolsMain.cpp
)

SET(TINKERCELL_BASICTOOLS_HDR
  CollisionDetection.h
  ConnectionInsertion.h
  ConnectionMaker.h
  ConnectionSelection.h
  DnaGraphicsItem.h
  GraphicsReplaceTool.h
  GraphicsTransformTool.h
  GroupHandlerTool.h
  NameFamilyDialog.h
  NodeInsertion.h
  NodeSelection.h
  TinkerCellAboutBox.h
  BasicToolsMain.cpp
)

QT4_WRAP_CPP( BasicTools_MOC ${TINKERCELL_BASICTOOLS_HDR} ${TINKERCELL_CORE_HDRS})

ADD_LIBRARY( BasicTools 
  SHARED
  ${BasicTools_MOC}
  ${TINKERCELL_BASICTOOLS_SRC}
  ${TINKERCELL_BASICTOOLS_QRC}
)

TARGET_LINK_LIBRARIES( BasicTools
  BasicTools
  NodesTree
  TinkerCellCore
)

INSTALL(TARGETS ${LIBANTIMONY_LIBRARY}
	RUNTIME DESTINATION ${TINKERCELL_PACKAGE_ROOT_DIR}/plugins
	LIBRARY DESTINATION ${TINKERCELL_PACKAGE_ROOT_DIR}/plugins
	ARCHIVE DESTINATION ${TINKERCELL_PACKAGE_ROOT_DIR}/plugins
)

