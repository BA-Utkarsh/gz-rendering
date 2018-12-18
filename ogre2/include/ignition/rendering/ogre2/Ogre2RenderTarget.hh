/*
 * Copyright (C) 2018 Open Source Robotics Foundation
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
#ifndef IGNITION_RENDERING_OGRE2_OGRE2RENDERTARGET_HH_
#define IGNITION_RENDERING_OGRE2_OGRE2RENDERTARGET_HH_

#include <ignition/math/Color.hh>

#include "ignition/rendering/base/BaseRenderTypes.hh"
#include "ignition/rendering/base/BaseRenderTarget.hh"
#include "ignition/rendering/ogre2/Ogre2Includes.hh"
#include "ignition/rendering/ogre2/Ogre2Object.hh"
#include "ignition/rendering/ogre2/Ogre2RenderTargetMaterial.hh"

namespace Ogre
{
  class Camera;
  class RenderTarget;
  class Texture;
}

namespace ignition
{
  namespace rendering
  {
    inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {
    //
    /// \brief Ogre2.x implementation of the render target class
    class IGNITION_RENDERING_OGRE2_VISIBLE Ogre2RenderTarget :
      public virtual BaseRenderTarget<Ogre2Object>
    {
      /// \brief Constructor
      protected: Ogre2RenderTarget();

      /// \brief Destructor
      public: virtual ~Ogre2RenderTarget();

      /// \brief Get the anti-aliasing level
      public: virtual unsigned int AntiAliasing() const;

      /// \brief set the anti-aliasing level
      /// \param[in] _aa Anti-aliasing level
      public: virtual void SetAntiAliasing(unsigned int _aa);

      /// \brief Copy the render target buffer data to an image
      /// \param[in] _image Image to copy the data to
      public: virtual void Copy(Image &_image) const override;

      /// \brief Get a pointer to the internal ogre camera
      /// \return Pointer to ogre camera
      public: virtual Ogre::Camera *Camera() const;

      /// \brief Set the ogre camera to use for this render target
      /// \param[in] _camera Pointer to ogre camera
      public: virtual void SetCamera(Ogre::Camera *_camera);

      // Documentation inherited
      public: virtual math::Color BackgroundColor() const override;

      /// \brief Set the background color of the render target
      /// \param[in] _color Color to set the background to
      public: virtual void SetBackgroundColor(math::Color _color);

      // Documentation inherited
      public: virtual void PreRender() override;

      // Documentation inherited
      public: virtual void PostRender() override;

      /// \brief Main render call
      public: virtual void Render();

      /// \brief Destroy the render target
      public: virtual void Destroy() override = 0;

      /// \brief Set a material to render on every object. This method is used
      /// for special cases like the render target of a depth camera.
      /// \param[in] _material The material to render
      public: void SetMaterial(MaterialPtr _material);

      /// \brief Get a pointer to the ogre render target
      public: virtual Ogre::RenderTarget *RenderTarget() const = 0;

      /// \brief Update the background color
      protected: virtual void UpdateBackgroundColor();

      /// \brief Implementation of the Rebuild function
      protected: virtual void RebuildImpl() override;

      /// \brief Rebuild the render target
      protected: virtual void RebuildTarget() = 0;

      /// \brief Rebuild the compositor
      protected: virtual void RebuildCompositor();

      /// \brief Build the comopsitor
      protected: virtual void BuildCompositor();

      /// \brief Destroy the compositor
      protected: virtual void DestroyCompositor();

      /// \brief Re-initializes render target material to apply a material to
      /// everything in the scene. Does nothing if no material has been set
      /// \sa Ogre2RenderTarget::RebuildImpl()
      /// \sa BaseRenderTarget::Rebuild()
      protected: void RebuildMaterial();

      /// \brief Pointer to the internal ogre camera
      protected: Ogre::Camera *ogreCamera = nullptr;

      /// \brief Ogre's compositor workspace - the main interface to render
      /// into a render target or render texture.
      protected: Ogre::CompositorWorkspace *ogreCompositorWorkspace = nullptr;

      /// \brief Stores the background color of the render target
      protected: Ogre::ColourValue ogreBackgroundColor;

      /// \brief a material used by for the render target
      protected: MaterialPtr material;

      /// \brief Helper class that applies the material to the render target
      protected: Ogre2RenderTargetMaterialPtr materialApplicator;

      /// \brief Flag to indicate if the render target color has changed
      protected: bool colorDirty = true;

      /// \brief Anti-aliasing level
      protected: unsigned int antiAliasing = 4;
    };

    /// \brief Ogre2.x implementation of the render texture class
    class IGNITION_RENDERING_OGRE2_VISIBLE Ogre2RenderTexture :
      public virtual BaseRenderTexture<Ogre2RenderTarget>
    {
      /// \brief Constructor
      protected: Ogre2RenderTexture();

      /// \brief Destructor
      public: virtual ~Ogre2RenderTexture();

      // Documentation inherited.
      public: virtual void Destroy() override;

      // Documentation inherited
      public: virtual void PreRender() override;

      // Documentation inherited
      public: virtual void PostRender() override;

      // Documentation inherited
      public: virtual GLuint GLId() const override;

      // Documentation inherited.
      public: virtual Ogre::RenderTarget *RenderTarget() const override;

      // Documentation inherited.
      protected: virtual void RebuildTarget() override;

      /// \brief Destroy the render texture
      protected: virtual void DestroyTarget();

      /// \brief Build the render texture
      protected: virtual void BuildTarget();

      /// \brief Pointer to the internal ogre render texture object
      protected: Ogre::Texture *ogreTexture = nullptr;

      /// \brief Make scene our friend so it can create a ogre2 render texture
      private: friend class Ogre2Scene;
    };

    /// \brief Ogre2.x implementation of the render window class
    class IGNITION_RENDERING_OGRE2_VISIBLE Ogre2RenderWindow :
      public virtual BaseRenderWindow<Ogre2RenderTarget>
    {
      /// \brief Constructor
      protected: Ogre2RenderWindow();

      /// \brief Destructor
      public: virtual ~Ogre2RenderWindow();

      // Documentation inherited.
      public: virtual void Destroy() override;

      // Documentation inherited.
      public: virtual Ogre::RenderTarget *RenderTarget() const override;

      // Documentation inherited.
      protected: virtual void RebuildTarget() override;

      /// \brief Build the render window
      protected: virtual void BuildTarget();

      /// \brief Pointer to the internal ogre render target object
      protected: Ogre::RenderTarget *ogreRenderWindow = nullptr;

      /// \brief Make scene our friend so it can create a ogre2 render window
      private: friend class Ogre2Scene;
    };
    }
  }
}
#endif
