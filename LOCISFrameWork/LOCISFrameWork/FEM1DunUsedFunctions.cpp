#include "FEM1D.h"
//#include "Operators.h"
#include <iostream>

ASTNode* FEM::dispatch(ASTmodel_collectionNode* node)
{
	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Process a model
ASTNode* FEM::dispatch(ASTmodelNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Process a group of model entities
ASTNode* FEM::dispatch(ASTmodel_entity_decl_groupNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Process each entity declared
ASTNode* FEM::dispatch(ASTmodel_entity_declNode* node)
{
	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTmodel_entities_collectionNode* node)
{
	return NULL;
}

ASTNode* FEM::dispatch(ASTmodel_sectionNode* node)
{
	return NULL;
}

ASTNode* FEM::dispatch(ASTgeneric_tokenNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASToptions_groupNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declare Unit for entity
ASTNode* FEM::dispatch(ASTunit_optionNode* node)
{

	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declare Description for entity
ASTNode* FEM::dispatch(ASTdesc_optionNode* node)
{

	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTtype_optionNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declare bounds for entity of type Variable only!
ASTNode* FEM::dispatch(ASTbounds_optionNode * node)
{

	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return the evaluated default value
ASTNode* FEM::dispatch(ASTdefualtNode* node)
{
	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Equation node (This is simply evaluated without using the returns, just to catch semantic errors)
ASTNode* FEM::dispatch(ASTequationNode* node)
{
	return node;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simply return a number node
ASTNode* FEM::dispatch(ASTNumberNode* node)
{

	if (node->bIsFEMtrialFunction)
	{
		std::cout << " Inside Number node";
	}



	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTNamedReferenceNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTArrayIndicesNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTarray_indexNode* node)
{
	return NULL;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Expression Evaluation(logical)
ASTNode* FEM::dispatch(ASTLogicalBinaryOpNode* node)
{
	return node;
}

ASTNode* FEM::dispatch(ASTLogicalUnaryNode* node)
{
	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// if statement
ASTNode* FEM::dispatch(ASTif_statmentNode* node)
{
	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// performs the for loop
ASTNode* FEM::dispatch(ASTfor_loopNode* node)
{
	return node;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTstatement_blockNode* node)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Assigns values
ASTNode* FEM::dispatch(ASTassignmentNode* node)
{
	return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTBasisTypeNode* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTSegmentAttributesNode* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTPdevarAttributesNode* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTSegmentIdTypeNode* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTNumelNode* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTLengthNode* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTdomainOptionNode* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTFEMoneDEquation* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTstringIndex* node)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ASTNode* FEM::dispatch(ASTDerivativeSingleVar* node)
{
	return NULL;
}

UNUSED_AST_NODE_FUNCTION(FEM, ASTBoundaryConditions)
UNUSED_AST_NODE_FUNCTION(FEM, ASTSimulationArgs)