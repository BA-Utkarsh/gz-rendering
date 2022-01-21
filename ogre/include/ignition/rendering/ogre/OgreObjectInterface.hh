/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef IGNITION_RENDERING_OGRE_OGREOBJECTINTERFACE_HH_
#define IGNITION_RENDERING_OGRE_OGREOBJECTINTERFACE_HH_

#include "ignition/rendering/config.hh"
#include "ignition/rendering/ogre/OgreIncludes.hh"
#include "ignition/rendering/ogre/Export.hh"

namespace ignition
{
  namespace rendering
  {
    inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {

    /// \brief Mixin class to provide direct access to Ogre objects.
    class IGNITION_RENDERING_OGRE_VISIBLE OgreObjectInterface
    {
      public: virtual ~OgreObjectInterface();

      /// \brief Access to an Ogre::MovableObject.
      //
      /// \param[in] _typename Name of the object type to retrieve.
      /// \return A pointer to an Ogre::MovableObject. Has default nullptr.
      public: virtual Ogre::MovableObject *OgreMovableObject(
          const char* _typename) const;

      /// \brief Access the Ogre::Camera object.
      //
      /// \return A pointer to an Ogre::Camera. Has default nullptr.
      public: virtual Ogre::Camera *Camera() const = 0;
    };
    }
  }
}
#endif