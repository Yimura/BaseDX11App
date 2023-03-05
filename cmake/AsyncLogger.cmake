include(FetchContent)
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY git@github.com:Yimura/AsyncLogger.git
    GIT_TAG master
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)