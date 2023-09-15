link_directories("/opt/ros/indigo/lib")

set(NODE_RPC_CLIENT_SRC
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcClient.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcDispatch.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcServer.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcServerConnection.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcServerMethod.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcSocket.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcSource.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcUtil.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcValue.cpp
	HelloClient.cpp
)

add_executable(rpc_client ${NODE_RPC_CLIENT_SRC})
IF(CMAKE_BUILD_TYPE MATCHES "release")
target_link_libraries(rpc_client libxmlrpc librobot)
ELSE()
target_link_libraries(rpc_client libxmlrpc librobot)
ENDIF()


set(NODE_RPC_SERVER_SRC
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcClient.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcDispatch.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcServer.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcServerConnection.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcServerMethod.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcSocket.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcSource.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcUtil.cpp
	#${KUNHOUIO_SDK_PATH}/src/xmlrpc_lib/XmlRpcValue.cpp
	HelloServer.cpp
)
add_executable(rpc_server ${NODE_RPC_SERVER_SRC})
IF(CMAKE_BUILD_TYPE MATCHES "release")
target_link_libraries(rpc_server libxmlrpc)
ELSE()
target_link_libraries(rpc_server libxmlrpc)
ENDIF()
