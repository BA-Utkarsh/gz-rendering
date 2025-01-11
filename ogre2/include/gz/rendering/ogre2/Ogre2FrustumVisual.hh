/*
 * Copyright (C) 2025 Open Source Robotics Foundation
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

#ifndef GZ_RENDERING_OGRE2_OGREFRUSTUMVISUAL_HH_
#define GZ_RENDERING_OGRE2_OGREFRUSTUMVISUAL_HH_

#include <memory>
#include <vector>
#include "gz/rendering/base/BaseFrustumVisual.hh"
#include "gz/rendering/ogre2/Ogre2Visual.hh"
#include "gz/rendering/ogre2/Ogre2Includes.hh"
#include "gz/rendering/ogre2/Ogre2Scene.hh"

namespace gz
{
  namespace rendering
  {
    inline namespace GZ_RENDERING_VERSION_NAMESPACE {
    //
    // Forward declaration
    class Ogre2FrustumVisualPrivate;

    /// \brief Ogre 2.x implementation of a Frustum Visual.
    class GZ_RENDERING_OGRE2_VISIBLE Ogre2FrustumVisual
      : public BaseFrustumVisual<Ogre2Visual>
    {
      /// \brief Constructor
      protected: Ogre2FrustumVisual();

      /// \brief Destructor
      public: virtual ~Ogre2FrustumVisual();

      // Documentation inherited.
      public: virtual void Init() override;

      // Documentation inherited.
      public: virtual void PreRender() override;

      // Documentation inherited.
      public: virtual void Destroy() override;

      // Documentation inherited
      public: virtual void Update() override;

      /// \brief Create the Frustum Visual in ogre
      private: void Create();

      /// \brief Clear data stored by dynamiclines
      private: void ClearVisualData();

      // Documentation inherited
      public: virtual void SetVisible(bool _visible) override;

      /// \brief Frustum Visual should only be created by scene.
      private: friend class Ogre2Scene;

      /// \brief Private data class
      private: std::unique_ptr<Ogre2FrustumVisualPrivate> dataPtr;
    };
    }
  }
}
#endif
