/**
 * Provides the ScopeLogger class that provides logging the Entry and Exit of
 * the scope where this class is defined using the information provided at
 * construction time.  The Exit scope will be logged with the line number of
 * the where the ScopeLogger class was defined.
 *
 * @file src/GQE/Core/loggers/ScopeLogger.cpp
 * @author Ryan Lindeman
 * @date 20110610 - Initial Release
 */
 
#include <GQE/Core/loggers/ScopeLogger.hpp>
 
namespace GQE
{
  ScopeLogger::ScopeLogger(SeverityType theSeverity,
      const char* theSourceFile, int theSourceLine,
      const char* theScopeName, int theExitCode) :
      ILogger(theExitCode),
      mSeverity(theSeverity),
      mSourceFile(theSourceFile),
      mSourceLine(theSourceLine),
      mScopeName(theScopeName)
  {
    // Make sure our global logger is defined before using it
    if(GQE::gLogger)
    {
      // Log the scope Entry with theScopeName provided to the
      // global logger (see GQE::gLogger).
      GQE::gLogger->GetStream(mSeverity, mSourceFile, mSourceLine,
        theExitCode) << "Enter(" << theScopeName << ") ";
    }
  }  

  ScopeLogger::~ScopeLogger()
  {
    // Make sure our global logger is defined before using it
    if(GQE::gLogger)
    {
      // Log the scope Exit with mScopeName provided at construction time to
      // the global logger (see GQE::gLogger).
      GQE::gLogger->GetStream(mSeverity, mSourceFile, mSourceLine)
        << "Exit(" << mScopeName << ")" << std::endl;
    }

    // If the severity level is Fatal then call our FatalShutdown method
    if(GQE::SeverityFatal == mSeverity)
    {
      FatalShutdown();
    }
  }

  std::ostream& ScopeLogger::GetStream(void)
  {
    // Make sure our global logger is defined before using it
    if(GQE::gLogger)
    {
      // Just return whatever the global logger returns for GetStream()
      return GQE::gLogger->GetStream();      
    }
    else
    {
      // If global logger doesn't exist, gNullStream will so return that
      return GQE::gNullStream;
    }
  }

  std::ostream& ScopeLogger::GetStream(SeverityType theSeverity,
      const char* theSourceFile, int theSourceLine, int theExitCode)
  {
    // Update our internal copy of the severity level, source file, and the
    // source line so our Exit entry can report the last time this method was
    // called (see SLOGR).
    mSeverity = theSeverity;
    mSourceFile = theSourceFile;
    mSourceLine = theSourceLine;

    // Make sure our global logger is defined before using it
    if(GQE::gLogger)
    {
      // Just return whatever the global logger returns for GetStream()
      return GQE::gLogger->GetStream(theSeverity, theSourceFile,
        theSourceLine, theExitCode) << "Result(" << mScopeName << ") ";      
    }
    else
    {
      // If global logger doesn't exist, gNullStream will so return that
      return GQE::gNullStream;
    }
  }
  
  void ScopeLogger::LogMessage(const char* theMessage)
  {
    // Make sure our global logger is defined before using it
    if(GQE::gLogger)
    {
      // Use the global logger to log theMessage provided
      GQE::gLogger->LogMessage(theMessage);      
    }
  }

  void ScopeLogger::LogMessage(SeverityType theSeverity,
      const char* theSourceFile, int theSourceLine,
      const char* theMessage)
  {
    // Update our internal copy of the severity level, source file, and the
    // source line so our Exit entry can report the last time this method was
    // called (see SLOGR).
    mSeverity = theSeverity;
    mSourceFile = theSourceFile;
    mSourceLine = theSourceLine;

    // Make sure our global logger is defined before using it
    if(GQE::gLogger)
    {
      // Use the global logger to log theMessage and other info provided
      GQE::gLogger->LogMessage(theSeverity, theSourceFile, theSourceLine,
        theMessage);      
    }
  }

} // namespace GQE