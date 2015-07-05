/******************************************************************************
Project	:	UNDONE Engine
File	:	GENERATE_FUNCTIONS.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------------------------------
This Header file contains macros which when the file is included with a 
preceding definition specifying the group of functions, automatically generates 
the functions involving Components of all types. Please Add the definition for
any new components you add later to this file so that the functons corresponding 
to that component can be generated automatically.
-------------------------------------------------------------------------------*/

#include "DPointer.h"

#define GENERATE_FUNCTIONS(type)
//For ObJectBuffer
#ifdef _GENFUNC_DEC_UNOBJECTBUFFER_H_
	#define  GENERATE_FUNCTIONS(type)																		\
		virtual void DeleteAll_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0) = 0;										\
		virtual UNDONE_ENGINE::DPointer<type> CreateNew_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0) = 0;							\
		virtual UNDONE_ENGINE::DPointer<type> Get_ ## type ## _ByName (const char* name, UNDONE_ENGINE::OwnerShip ownership = 0) = 0; 
	#undef _GENFUNC_DEC_UNOBJECTBUFFER_H_
#elif defined _GENFUNC_DEC_DOBJECTBUFFER_H_
	#define GENERATE_FUNCTIONS(type)																		\
		void DeleteAll_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0);													\
		UNDONE_ENGINE::DPointer<type> CreateNew_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0);										\
		UNDONE_ENGINE::DPointer<type> Get_ ## type ## _ByName (const char* name, UNDONE_ENGINE::OwnerShip ownership = 0);
	#undef _GENFUNC_DEC_DOBJECTBUFFER_H_
#elif defined _GENFUNC_DEF_DOBJECTBUFFER_CPP_
	#define GENERATE_FUNCTIONS(type)																			\
	void DObjectBuffer::DeleteAll_ ## type (UNDONE_ENGINE::OwnerShip ownership){											\
		DeleteAll<type>(ownership);																			\
		}																									\
	UNDONE_ENGINE::DPointer<type> DObjectBuffer::CreateNew_ ## type (UNDONE_ENGINE::OwnerShip ownership){									\
		return CreateNew<type>(ownership);																		\
		}																									\
	UNDONE_ENGINE::DPointer<type> DObjectBuffer::Get_ ## type ## _ByName (const char* name, UNDONE_ENGINE::OwnerShip ownership){			\
		return GetComponentByNameOfType<type>(name, ownership);												\
		}
	#undef _GENFUNC_DEF_DOBJECTBUFFER_CPP_

//for DPointer
#elif defined _GENFUNC_DEC_DPOINTER_H_
	#define GENERATE_FUNCTIONS(type)\
	template struct DPointer<type>;
	#undef _GENFUNC_DEC_DPOINTER_H_

//General use
#elif defined _GEN_FORWARD_DEC_COMPS_
	#define GENERATE_FUNCTIONS(type)\
	class type;
	#undef _GEN_FORWARD_DEC_COMPS_
#elif defined _GEN_FORWARD_DEC_COMPS_INT_
	#define GENERATE_FUNCTIONS(type)\
		class un ## type;
	#undef _GEN_FORWARD_DEC_COMPS_INT_

//For GameObject
#elif defined _GENFUNC_DEC_UNGAMEOBJECT_H_
	#define GENERATE_FUNCTIONS(type)\
		virtual UNDONE_ENGINE::DPointer<un##type> Get ## type() = 0;\
		virtual void Add ## type (UNDONE_ENGINE::DPointer<un ## type> rComponent) = 0;\
		virtual void Remove ## type () = 0;\
		virtual void Remove ## type ## byName(const char* name) = 0;
	#undef _GENFUNC_DEC_UNGAMEOBJECT_H_
#elif defined _GENFUNC_DEC_GAMEOBJECT_H_
	#define GENERATE_FUNCTIONS(type)\
		virtual UNDONE_ENGINE::DPointer<un##type> Get ## type();\
		virtual void Add ## type (UNDONE_ENGINE::DPointer<un ## type> rComponent);\
		virtual void Remove## type();\
		virtual void Remove## type ## byName(const char* name);
	#undef _GENFUNC_DEC_GAMEOBJECT_H_
#elif defined _GENFUNC_DEF_GAMEOBJECT_CPP_
#define GENERATE_FUNCTIONS(type)\
		DPointer<un ## type> GameObject::Get ## type(){\
			return dcast<un ## type,type>(GetComponent<type>());\
		}\
		void GameObject::Add ## type (DPointer<un ## type> rComponent){\
			 AddComponent<type>(dcast<type,un ## type>(rComponent));\
		}\
		void GameObject::Remove ## type (){\
			RemoveComponent<type>();\
		}\
		void GameObject::Remove ## type ## byName(const char* name){\
			RemoveComponentByName(name);\
		}
		#undef _GENFUNC_DEF_GAMEOBJECT_CPP_

#endif

#include "DPointer.h"

	/*--------------------------------------------------------------------------
	Please insert a Macro call to GENERATE_FUNCTIONS for each new Component
	you create under here.
	-------------------------------------------------------------------------*/
#define GENFUNCS()\
		GENERATE_FUNCTIONS(GameObject)\
		GENERATE_FUNCTIONS(WorldTransform)\
		GENERATE_FUNCTIONS(Mesh)\
		GENERATE_FUNCTIONS(GraphicMaterial)\
		GENERATE_FUNCTIONS(_3DGraphic)\
		GENERATE_FUNCTIONS(_2DGraphic)\
		GENERATE_FUNCTIONS(Texture)\
		GENERATE_FUNCTIONS(Shader)\
		GENERATE_FUNCTIONS(ShaderProgram)\



