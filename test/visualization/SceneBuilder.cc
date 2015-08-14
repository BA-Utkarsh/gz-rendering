/*
 * Copyright (C) 2015 Open Source Robotics Foundation
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
#include "SceneBuilder.hh"

using namespace ignition;
using namespace rendering;

//////////////////////////////////////////////////
//////////////////////////////////////////////////

unsigned int SceneBuilder::tick = 0;

//////////////////////////////////////////////////
SceneBuilder::SceneBuilder()
{
}

//////////////////////////////////////////////////
SceneBuilder::~SceneBuilder()
{
}

//////////////////////////////////////////////////
void SceneBuilder::SetScenes(const SceneList &_scenes)
{
  this->scenes = _scenes;
  this->RegisterMaterials();
}

//////////////////////////////////////////////////
void SceneBuilder::SetCameras(const CameraList &_cameras)
{
  this->cameras = _cameras;
}

//////////////////////////////////////////////////
void SceneBuilder::BuildScenes()
{
  for (auto scene : this->scenes)
  {
    this->ClearScene(scene);
    this->BuildScene(scene);
  }
}

//////////////////////////////////////////////////
void SceneBuilder::ResetCameras()
{
  for (auto camera : this->cameras)
  {
    this->ResetCamera(camera);
  }
}

//////////////////////////////////////////////////
void SceneBuilder::UpdateScenes()
{
  for (auto scene : this->scenes)
  {
    this->UpdateScene(scene);
  }

  ++tick;
}

//////////////////////////////////////////////////
void SceneBuilder::ClearScene(ScenePtr _scene)
{
  _scene->DestroyLights();
  _scene->DestroyVisuals();
}

//////////////////////////////////////////////////
void SceneBuilder::BuildScene(ScenePtr _scene)
{
  _scene->SetBackgroundColor(0.2, 0.2, 0.2);
}

//////////////////////////////////////////////////
void SceneBuilder::ResetCamera(CameraPtr)
{
  // do nothing by default
}

//////////////////////////////////////////////////
void SceneBuilder::UpdateScene(ScenePtr)
{
  // do nothing by default
}

//////////////////////////////////////////////////
void SceneBuilder::RegisterMaterials()
{
  for (auto scene : this->scenes)
  {
    this->RegisterMaterials(scene);
  }
}

//////////////////////////////////////////////////
void SceneBuilder::RegisterMaterials(ScenePtr _scene)
{
  if (!_scene->MaterialRegistered("Red"))
  {
    MaterialPtr mat = _scene->CreateMaterial();
    mat->SetAmbient(0.3, 0.0, 0.0);
    mat->SetDiffuse(0.8, 0.0, 0.0);
    mat->SetSpecular(0.8, 0.8, 0.8);
    mat->SetShininess(50);
    mat->SetReflectivity(0);
    _scene->RegisterMaterial("Red", mat);
  }

  if (!_scene->MaterialRegistered("White"))
  {
    MaterialPtr mat = _scene->CreateMaterial();
    mat->SetAmbient(0.8, 0.8, 0.8);
    mat->SetDiffuse(0.6, 0.6, 0.6);
    mat->SetSpecular(0.8, 0.8, 0.8);
    mat->SetShininess(50);
    mat->SetReflectivity(0);
    _scene->RegisterMaterial("White", mat);
  }


  if (!_scene->MaterialRegistered("Green"))
  {
    MaterialPtr mat = _scene->CreateMaterial();
    mat->SetAmbient(0.0, 0.3, 0.0);
    mat->SetDiffuse(0.0, 0.8, 0.0);
    mat->SetSpecular(0.8, 0.8, 0.8);
    mat->SetShininess(50);
    mat->SetReflectivity(0);
    _scene->RegisterMaterial("Green", mat);
  }

  if (!_scene->MaterialRegistered("Blue"))
  {
    MaterialPtr mat = _scene->CreateMaterial();
    mat->SetAmbient(0.0, 0.0, 0.3);
    mat->SetDiffuse(0.0, 0.0, 0.8);
    mat->SetSpecular(0.8, 0.8, 0.8);
    mat->SetShininess(50);
    mat->SetReflectivity(0);
    _scene->RegisterMaterial("Blue", mat);
  }

  if (!_scene->MaterialRegistered("Yellow"))
  {
    MaterialPtr mat = _scene->CreateMaterial();
    mat->SetAmbient(0.3, 0.3, 0.0);
    mat->SetDiffuse(0.8, 0.8, 0.0);
    mat->SetSpecular(0.8, 0.8, 0.8);
    mat->SetShininess(50);
    mat->SetReflectivity(0);
    _scene->RegisterMaterial("Yellow", mat);
  }

  std::vector<std::string> baseNames;
  baseNames.push_back("Blue");
  baseNames.push_back("Green");
  baseNames.push_back("Red");
  baseNames.push_back("White");
  baseNames.push_back("Yellow");

  for (auto baseName : baseNames)
  {
    std::string parentName = baseName;
    std::string childName = "Texture" + baseName;

    if (!_scene->MaterialRegistered(childName))
    {
      MaterialPtr mat = _scene->GetMaterial(parentName)->Clone();
      mat->SetTexture("/home/mike/Downloads/tiles.jpg");
      _scene->RegisterMaterial(childName, mat);
    }
  }

  for (auto baseName : baseNames)
  {
    std::string parentName = "Texture" + baseName;
    std::string childName = "Reflect" + baseName;

    if (!_scene->MaterialRegistered(childName))
    {
      MaterialPtr mat = _scene->GetMaterial(parentName)->Clone();
      mat->SetReflectivity(0.1);
      _scene->RegisterMaterial(childName, mat);
    }
  }
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

const std::string SimpleSceneBuilder::LIGHT("Light");

const std::string SimpleSceneBuilder::SPHERE("Sphere");

const std::string SimpleSceneBuilder::PLANE("Plane");

//////////////////////////////////////////////////
SimpleSceneBuilder::SimpleSceneBuilder()
{
}

//////////////////////////////////////////////////
SimpleSceneBuilder::~SimpleSceneBuilder()
{
}

//////////////////////////////////////////////////
void SimpleSceneBuilder::BuildScene(ScenePtr _scene)
{
  SceneBuilder::BuildScene(_scene);
  VisualPtr root = _scene->GetRootVisual();
  _scene->SetAmbientLight(0.1, 0.1, 0.1);

  DirectionalLightPtr light = _scene->CreateDirectionalLight(LIGHT);
  light->SetDirection(0.3, 0.5, -1.0);
  light->SetDiffuseColor(0.8, 0.8, 0.8);
  light->SetSpecularColor(0.8, 0.8, 0.8);
  root->AddChild(light);

  VisualPtr sphere = _scene->CreateVisual(SPHERE);
  sphere->AddGeometry(_scene->CreateSphere());
  sphere->SetLocalPosition(3.0, 0.0, 0.5);
  sphere->SetLocalRotation(0.0, 0.0, 0.0);
  sphere->SetMaterial("Red");
  root->AddChild(sphere);

  VisualPtr plane = _scene->CreateVisual(PLANE);
  plane->AddGeometry(_scene->CreatePlane());
  plane->SetLocalPosition(3.0, 0.0, 0.0);
  plane->SetLocalRotation(0.0, 0.0, 0.0);
  plane->SetLocalScale(5.0, 50.0, 1.0);
  plane->SetMaterial("White");
  root->AddChild(plane);
}

//////////////////////////////////////////////////
void SimpleSceneBuilder::ResetCamera(CameraPtr _camera)
{
  _camera->SetLocalPosition(0.5, 0.0, 1.0);
  _camera->SetLocalRotation(0.0, 0.1, 0.0);
}

//////////////////////////////////////////////////
void SimpleSceneBuilder::UpdateScene(ScenePtr _scene)
{
  SceneBuilder::UpdateScene(_scene);
  double scale = cos(this->tick * 0.05);

  VisualPtr sphere = _scene->GetVisualByName(SPHERE);
  gazebo::math::Pose pose = sphere->GetLocalPose();
  pose.pos.z = 0.6 + scale * 0.1;
  sphere->SetLocalPose(pose);
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

const std::string AllShapesSceneBuilder::CONE("Cone");

const std::string AllShapesSceneBuilder::CYLINDER("Cylinder");

const std::string AllShapesSceneBuilder::BOX("Box");

//////////////////////////////////////////////////
AllShapesSceneBuilder::AllShapesSceneBuilder()
{
}

//////////////////////////////////////////////////
AllShapesSceneBuilder::~AllShapesSceneBuilder()
{
}

//////////////////////////////////////////////////
void AllShapesSceneBuilder::BuildScene(ScenePtr _scene)
{
  SimpleSceneBuilder::BuildScene(_scene);
  VisualPtr root = _scene->GetRootVisual();

  VisualPtr cylinder = _scene->CreateVisual(CYLINDER);
  cylinder->AddGeometry(_scene->CreateCylinder());
  cylinder->SetLocalPosition(3.3, 1.0, 0.5);
  cylinder->SetLocalRotation(0.0, -0.5, 0.0);
  cylinder->SetLocalScale(0.5, 0.5, 1.5);
  cylinder->SetMaterial("Green");
  root->AddChild(cylinder);

  VisualPtr cone = _scene->CreateVisual(CONE);
  cone->AddGeometry(_scene->CreateCone());
  cone->SetLocalPosition(2.6, -0.8, 1.2);
  cone->SetLocalRotation(-0.5, -0.75, 0.0);
  cone->SetLocalScale(0.8, 0.8, 1.0);
  cone->SetMaterial("Blue");
  root->AddChild(cone);

  VisualPtr box = _scene->CreateVisual(BOX);
  box->AddGeometry(_scene->CreateBox());
  box->SetLocalPosition(2.2, -0.8, 0.2);
  box->SetLocalRotation(M_PI / 4, 0.0, M_PI / 4);
  box->SetLocalScale(0.5, 0.5, 0.5);
  box->SetMaterial("Yellow");
  root->AddChild(box);
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
TextureSceneBuilder::TextureSceneBuilder()
{
}

//////////////////////////////////////////////////
TextureSceneBuilder::~TextureSceneBuilder()
{
}

//////////////////////////////////////////////////
void TextureSceneBuilder::BuildScene(ScenePtr _scene)
{
  AllShapesSceneBuilder::BuildScene(_scene);

  VisualPtr box = _scene->GetVisualByName(BOX);
  box->SetMaterial("TextureYellow");

  VisualPtr cone = _scene->GetVisualByName(CONE);
  cone->SetMaterial("TextureBlue");

  VisualPtr cylinder = _scene->GetVisualByName(CYLINDER);
  cylinder->SetMaterial("TextureGreen");

  VisualPtr plane = _scene->GetVisualByName(PLANE);
  plane->SetMaterial("TextureWhite");

  VisualPtr sphere = _scene->GetVisualByName(SPHERE);
  sphere->SetMaterial("TextureRed");
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
ReflectionSceneBuilder::ReflectionSceneBuilder()
{
}

//////////////////////////////////////////////////
ReflectionSceneBuilder::~ReflectionSceneBuilder()
{
}

//////////////////////////////////////////////////
void ReflectionSceneBuilder::BuildScene(ScenePtr _scene)
{
  TextureSceneBuilder::BuildScene(_scene);

  VisualPtr box = _scene->GetVisualByName(BOX);
  box->SetMaterial("ReflectYellow");

  VisualPtr cone = _scene->GetVisualByName(CONE);
  cone->SetMaterial("ReflectBlue");

  VisualPtr cylinder = _scene->GetVisualByName(CYLINDER);
  cylinder->SetMaterial("ReflectGreen");

  VisualPtr plane = _scene->GetVisualByName(PLANE);
  plane->SetMaterial("ReflectWhite");

  VisualPtr sphere = _scene->GetVisualByName(SPHERE);
  sphere->SetMaterial("ReflectRed");
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
ShadowSceneBuilder::ShadowSceneBuilder(unsigned int _n, double _dist) :
  n(_n),
  dist(_dist)
{
}

//////////////////////////////////////////////////
ShadowSceneBuilder::~ShadowSceneBuilder()
{
}

//////////////////////////////////////////////////
void ShadowSceneBuilder::BuildScene(ScenePtr _scene)
{
  SimpleSceneBuilder::BuildScene(_scene);
  _scene->DestroyLightByName(LIGHT);
  
  PointLightPtr light = _scene->CreatePointLight();
  light->SetLocalPosition(5.5, -2.0, 4.75);
  light->SetDiffuseColor(0.6, 0.6, 0.6);
  light->SetSpecularColor(0.8, 0.8, 0.8);
  this->AddLight(light, _scene);
}

//////////////////////////////////////////////////
void ShadowSceneBuilder::AddLight(PointLightPtr _light, ScenePtr _scene)
{
  VisualPtr root = _scene->GetRootVisual();
  unsigned int total = this->n * this->n * this->n;
  double step = (this->n == 1) ? 0 : this->dist / (this->n - 1);
  double factor = 1.0 / total;

  gazebo::math::Vector3 position = _light->GetLocalPosition();
  double offset = (this->n == 1) ? 0 : this->dist / 2;
  double x0 = position.x - offset;
  double y0 = position.y - offset;
  double z0 = position.z - offset;

  gazebo::common::Color diffuse;
  diffuse = _light->GetDiffuseColor();
  diffuse = diffuse * factor;

  gazebo::common::Color specular;
  specular = _light->GetSpecularColor();
  specular = specular * factor;

  for (unsigned int i = 0; i < this->n; ++i)
  {
    for (unsigned int j = 0; j < this->n; ++j)
    {
      for (unsigned int k = 0; k < this->n; ++k)
      {
        gazebo::math::Vector3 subPosition;
        subPosition.x = i * step + x0;
        subPosition.y = j * step + y0;
        subPosition.z = k * step + z0;

        PointLightPtr sublight = _scene->CreatePointLight();
        sublight->SetLocalPosition(subPosition);
        sublight->SetDiffuseColor(diffuse);
        sublight->SetSpecularColor(specular);
        root->AddChild(sublight);
      }
    }
  }
}
