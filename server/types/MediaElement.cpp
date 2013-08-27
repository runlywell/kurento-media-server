/*
 * MediaElement.cpp - Kurento Media Server
 *
 * Copyright (C) 2013 Kurento
 * Contact: Miguel París Díaz <mparisdiaz@gmail.com>
 * Contact: José Antonio Santos Cadenas <santoscadenas@kurento.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MediaElement.hpp"

#define GST_CAT_DEFAULT kurento_media_element
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);
#define GST_DEFAULT_NAME "KurentoMediaElement"

namespace kurento
{

MediaElement::MediaElement (std::shared_ptr<MediaObjectImpl> parent) : MediaObjectImpl (parent)
{
}

MediaElement::~MediaElement () throw ()
{

}

std::shared_ptr<MediaSrc>
MediaElement::getOrCreateAudioMediaSrc()
{
  mutex.lock();

  std::shared_ptr<MediaSrc> locked;

  try {
    locked = audioMediaSrc.lock();
  } catch (std::bad_weak_ptr e) {
  }

  if (locked.get() == NULL) {
    locked = std::shared_ptr<MediaSrc> (new  MediaSrc (shared_from_this(), MediaType::type::AUDIO) );
    audioMediaSrc = std::weak_ptr<MediaSrc> (locked);
  }

  mutex.unlock();

  return locked;
}

std::shared_ptr<MediaSrc>
MediaElement::getOrCreateVideoMediaSrc()
{
  mutex.lock();

  std::shared_ptr<MediaSrc> locked;

  try {
    locked = videoMediaSrc.lock();
  } catch (std::bad_weak_ptr e) {
  }

  if (locked.get() == NULL) {
    locked = std::shared_ptr<MediaSrc> (new  MediaSrc (shared_from_this(), MediaType::type::VIDEO) );
    videoMediaSrc = std::weak_ptr<MediaSrc> (locked);
  }

  mutex.unlock();

  return locked;
}

std::shared_ptr<MediaSink>
MediaElement::getOrCreateAudioMediaSink()
{
  mutex.lock();

  std::shared_ptr<MediaSink> locked;

  try {
    locked = audioMediaSink.lock();
  } catch (std::bad_weak_ptr e) {
  }

  if (locked.get() == NULL) {
    locked = std::shared_ptr<MediaSink> (new  MediaSink (shared_from_this(), MediaType::type::AUDIO) );
    audioMediaSink = std::weak_ptr<MediaSink> (locked);
  }

  mutex.unlock();

  return locked;
}

std::shared_ptr<MediaSink>
MediaElement::getOrCreateVideoMediaSink()
{
  mutex.lock();

  std::shared_ptr<MediaSink> locked;

  try {
    locked = videoMediaSink.lock();
  } catch (std::bad_weak_ptr e) {
  }

  if (locked.get() == NULL) {
    locked = std::shared_ptr<MediaSink> (new  MediaSink (shared_from_this(), MediaType::type::VIDEO) );
    videoMediaSink = std::weak_ptr<MediaSink> (locked);
  }

  mutex.unlock();

  return locked;
}

std::vector < std::shared_ptr<MediaSrc> > *
MediaElement::getMediaSrcs ()
{
  std::vector < std::shared_ptr<MediaSrc> > *mediaSrcs = new std::vector< std::shared_ptr<MediaSrc> >();

  mediaSrcs->push_back (getOrCreateAudioMediaSrc() );
  mediaSrcs->push_back (getOrCreateVideoMediaSrc() );

  return mediaSrcs;
}

std::vector < std::shared_ptr<MediaSink> > *
MediaElement::getMediaSinks()
{
  std::vector< std::shared_ptr<MediaSink> > *mediaSinks = new std::vector< std::shared_ptr<MediaSink> >();

  mediaSinks->push_back (getOrCreateAudioMediaSink() );
  mediaSinks->push_back (getOrCreateVideoMediaSink() );

  return mediaSinks;
}

std::vector < std::shared_ptr<MediaSrc> > *
MediaElement::getMediaSrcsByMediaType (const MediaType::type mediaType)
{
  std::vector < std::shared_ptr<MediaSrc> > *mediaSrcs = new std::vector< std::shared_ptr<MediaSrc> >();

  if (mediaType == MediaType::type::AUDIO)
    mediaSrcs->push_back (getOrCreateAudioMediaSrc() );
  else if (mediaType == MediaType::type::VIDEO)
    mediaSrcs->push_back (getOrCreateVideoMediaSrc() );

  return mediaSrcs;
}

std::vector < std::shared_ptr<MediaSink> > *
MediaElement::getMediaSinksByMediaType (const MediaType::type mediaType)
{
  std::vector< std::shared_ptr<MediaSink> > *mediaSinks = new std::vector< std::shared_ptr<MediaSink> >();

  if (mediaType == MediaType::type::AUDIO)
    mediaSinks->push_back (getOrCreateAudioMediaSink() );
  else if (mediaType == MediaType::type::VIDEO)
    mediaSinks->push_back (getOrCreateVideoMediaSink() );

  return mediaSinks;
}

MediaElement::StaticConstructor MediaElement::staticConstructor;

MediaElement::StaticConstructor::StaticConstructor()
{
  GST_DEBUG_CATEGORY_INIT (GST_CAT_DEFAULT, GST_DEFAULT_NAME, 0,
      GST_DEFAULT_NAME);
}

} // kurento