#include "Application.h"
#include "EmitterInstance.h"
#include "ParticleEmitter.h"
#include "ModuleSceneLoader.h"
#include "Libraries\glew/glew.h"
#include "Color.h"
#include "Component_ParticleSystem.h"
#include "Component_Billboard.h"
#include "ModuleTimeManagement.h"
#include "ModuleCamera3D.h"
#include "GameObject.h"

EmitterInstance::EmitterInstance()
{   
     
}

void EmitterInstance::Init(ParticleEmitter* emitterReference)
{
    this->emitter = emitterReference;
}

void EmitterInstance::UpdateModules()
{
    for (uint i = 0; i < emitter->modules.size() ; ++i)
    {
        emitter->modules[i]->Update(this);
    } 
}

void EmitterInstance::UpdateParticleReference()
{
    for (uint i = 0; i < emitter->modules.size(); ++i)
    {
        emitter->modules[i]->UpdateParticleReference(this);
    }
}