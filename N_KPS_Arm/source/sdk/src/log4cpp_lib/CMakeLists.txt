#Log4cpp Lib

INCLUDE_DIRECTORIES ( . )

IF (WIN32)
  ADD_DEFINITIONS ( -D_CRT_SECURE_NO_WARNINGS )
ELSE (WIN32)
  IF (APPLE)
    ADD_DEFINITIONS ( -DNDEBUG -DLOG4CPP_HAVE_SSTREAM )
  ELSE (APPLE)
    ADD_DEFINITIONS ( -pthread -DNDEBUG -DLOG4CPP_HAVE_SSTREAM )
  ENDIF (APPLE)
ENDIF (WIN32)


ADD_LIBRARY (liblog4cpp
  Appender.cpp
  AppenderSkeleton.cpp
  AppendersFactory.cpp
  BufferingAppender.cpp
  FactoryParams.cpp
  LayoutsFactory.cpp
  LevelEvaluator.cpp
  Localtime.cpp
  PassThroughLayout.cpp
  TriggeringEventEvaluatorFactory.cpp
  LayoutAppender.cpp
  FileAppender.cpp
  DailyRollingFileAppender.cpp
  RollingFileAppender.cpp
  FixedContextCategory.cpp
  IdsaAppender.cpp
  OstreamAppender.cpp
  StringQueueAppender.cpp
  SyslogAppender.cpp
  RemoteSyslogAppender.cpp
  SimpleLayout.cpp
  BasicLayout.cpp
  PatternLayout.cpp
  Category.cpp
  CategoryStream.cpp
  HierarchyMaintainer.cpp
  Configurator.cpp
  BasicConfigurator.cpp
  SimpleConfigurator.cpp
  PropertyConfigurator.cpp
  PropertyConfiguratorImpl.cpp
  LoggingEvent.cpp
  Priority.cpp
  NDC.cpp
  Filter.cpp
  TimeStamp.cpp
  StringUtil.cpp
  Properties.cpp
  Win32DebugAppender.cpp
  NTEventLogAppender.cpp
  DllMain.cpp
  DummyThreads.cpp
  MSThreads.cpp
  OmniThreads.cpp
  PThreads.cpp
  PortabilityImpl.cpp
  AbortAppender.cpp
)

IF (WIN32)

  target_link_libraries (liblog4cpp kernel32 user32 ws2_32 advapi32 )
  
ENDIF (WIN32)

IF(BUILD_SDK)
	INSTALL(TARGETS liblog4cpp DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)
