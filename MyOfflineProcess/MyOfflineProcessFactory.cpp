#include "MyOfflineProcessFactory.hpp"

#include <Media/Sound/SoundModel.hpp>
#include <Media/Commands/ChangeAudioFile.hpp>

#include <score/document/DocumentContext.hpp>
#include <score/command/Dispatchers/CommandDispatcher.hpp>

#include <core/document/Document.hpp>

#include <ossia/audio/drwav_handle.hpp>

#include <QDir>

namespace MyOfflineProcess
{
QString GainDoubler::title() const noexcept 
{
  return QObject::tr("GainDoubler");
}

UuidKey<Process::ProcessModel> GainDoubler::target() const noexcept {
  return Metadata<ConcreteKey_k, Media::Sound::ProcessModel>::get();
}

void GainDoubler::apply(
    Process::ProcessModel& proc,
    const score::DocumentContext& ctx) 

{
  auto& sound = safe_cast<Media::Sound::ProcessModel&>(proc);
  auto& file = sound.file();

  // Current file path:
  qDebug() << file->absoluteFileName();

  // Get the data: (note: this performs a copy and could be slow for large files)
  auto array = file->getAudioArray();

  // Perform our offline processing
  for(auto& channel : array)
  {
    for(ossia::audio_sample& c : channel)
    {
      c *= 2.0f;
    }
  }

  // Check if we have a project folder
  if(auto path = ctx.document.metadata().projectFolder(); !path.isEmpty())
  {
    // Get a new file name in the project folder
    auto newFilename = score::newProcessedFilePath(file->absoluteFileName(), QDir(path + QDir::separator() + "Processed"));
    qDebug() << newFilename;

    // Create the path if necessary
    QDir{path}.mkpath(QFileInfo(newFilename).absolutePath());

    // Save the data in the .wav file
    Media::writeAudioArrayToFile(newFilename, array, file->sampleRate());

    // Tell the process to load the new file
    CommandDispatcher<> cmd{ctx.commandStack};
    cmd.submit<Media::LoadProcessedAudioFile>(sound, newFilename);
  }
  else
  {
    qDebug() << "Could not save processed file ! "
                "You must save the score project somewhere beforehand.";
  }
}
}
