/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Undone_Engine.h"
#include "ObjectBuffer.h"
#include "SystemComponent.h"
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {
	ObjectBuffer::ObjectBuffer( ) {
		m_empty = true;
		m_init_vec_size = 100;
		m_num_owners = 0;
	}
	/*-------------------------------------------------------------------------
	DEfault Destructor.
	-------------------------------------------------------------------------*/
	ObjectBuffer::~ObjectBuffer( ) {
		if (m_storage_vectors.size( )!=0) {
			SystemComponent::GetInstance( )->ShowMessage("Some types of objects were not released",
														 "MEMORY LEAK WARNING!");
		}
		m_Components.clear( );
		m_pointer_table_lists.clear( );
		m_storage_vectors.clear( );
		m_storage_types.clear( );
		m_empty = true;
	}

	/*----------------------------------------------------------------------------
	Returns a Components with the given name.
	Parameters:
	[IN]	name	-	the name of the required Component.
	Returns:
	THe required component if it exists, otherwise a DPOINTER with a nullptr
	----------------------------------------------------------------------------*/
	Dptr<Component> ObjectBuffer::GetComponentByName(const char* name,OwnerShip ownership) {
		for (Dptr<Component>& component : m_Components) {
			if (component->name==name) {
				return component;
			}
		}

		//If the program got untill here, that means there isn't a component 
		//present with that name, so we give out a fake one.
		Dptr<Component> ErrorComponent;
		ErrorComponent.m_pointer = nullptr;
		return ErrorComponent;
	}

	#define _GENFUNC_DEF_DOBJECTBUFFER_CPP_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()
}