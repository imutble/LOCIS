#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "lexer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// All defines
#define SY_SCALAR			 0
#define SY_VECTOR			 1
#define SY_TYPE_REAL		 0
#define SY_TYPE_INT		 1
#define SY_TYPE_OBJECT		 2
#define SY_TYPE_MODEL		 3
#define SY_VAL_NOT_SET	     -1
#define SY_VAL_NOT_SETC	 'N'
#define SY_LARGE_NEGATIVE   1.0e-300
#define SY_LARGE_POSITIVE   1.0e300
#define SY_DEFAULT_VAL		 0.0
#define SY_INDEX_OUT_OF_RANGE -1
#define SY_INVALID_INDEX_POSITION -2;
#define SY_DIMS_ZERO -3;
#define SY_VECTOR_NOT_ALLOCATED -4
#define SY_VECTOR_FAILED_TO_ALLOCATE -5
#define SY_VECTOR_ALREADY_ALLOCATED -6
#define SY_INDEX_GT_1 -7;
#define SY_NOT_INITIALIZED -8;
#define SY_FAIL 0;
#define SY_SUCCESS 1
#define SY_PARAMETER_TYPE 1
#define SY_VARIABLE_TYPE 2
#define SY_OBJECT_TYPE 3
#define SY_FIX		1
#define SY_FREE    2
#define SY_LESS_THAN_OR_EQUAL 'A'
#define SY_GREATER_THAN_OR_EQUAL 'B'
#define SY_LESS_THAN 'C'
#define SY_GREATER_THAN 'D'
#define SY_VARIABLE_UBT 0
#define SY_VARIABLE_LBT 1
#define SY_VARIABLE_FT 2

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define all class types so that can be used in any order
class modelCollection;
class modelEntity;
class parameter;
class variable;
class object;
class model;
class interpreter;
class ASTNode;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FEM oneD context
class modelEntityFEMoneDContext
{
    //FEM one D flags
    bool isFEMoneDDomain;
    bool isFEMOneDLine;
    bool isFEMOneDVariable;
    bool isFEMOneDdVariable;
    bool isFEMtrialFunction;
    bool isTval;
    bool isFEMxval;
    modelEntity* currentDomain;

public:
    modelEntityFEMoneDContext();

    // Set
    void setIsFEMoneDDomain(bool value);
    void setIsFEMOneDLine(bool value);
    void setIsFEMOneDVariable(bool value);
    void setIsFEMOneDdVariable(bool value);
    void setIsFEMtrialFunction(bool value);
    void setIsTval(bool value);
    void setIsFEMxval(bool value);
    void setCurrentDomain(modelEntity* currentDomain_arg);

    bool getIsFEMoneDDomain();
    bool getIsFEMOneDLine();
    bool getIsFEMOneDVariable();
    bool getIsFEMOneDdVariable();
    bool getIsFEMtrialFunction();
    bool getIsTval();
    bool getIsFEMxval();
    modelEntity* getCurrentDomain();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Abstract class types for a basic entity in a simulation
class modelEntity
{
public:

    // Thesee flags are to be removed
    bool isFEMoneDDomain;
    bool isFEMOneDLine;
    bool isFEMOneDVariable;
    bool isFEMOneDdVariable;
    bool isFEMtrialFunction;
    bool isTval;
    bool isFEMxval;
    modelEntity* currentDomain;

    // Values (these should be the only public members
    double sValue;
    double *vValue;

    //Numbering for Variables
    int nSValue;
    int *nVValue;

protected:
	//Option flags
	bool bHasDesc;
	bool bHasUnit;
	bool bHasBounds[4];

    //FEM one D flags
    modelEntityFEMoneDContext meFEMContext;

	// Primitives
    modelEntity* other;
	bool isdt;

    //Lazy evaluation for vector initialization
    bool vectorIsInitialized;
    ASTNode* buildNode;

    // Info
	token* tok;       //Stores the token for the Symbol
    std::string name;
    std::string desc;
    std::string unit;

    int type;
    std::string sType;
    int nType;

	// Dimensions
    int dimType;
    std::vector<int> dims;
    std::vector<int> dimsC;
    long int maxdim;

public:
    modelEntity();
    virtual ~modelEntity();

    void setBHasDesc(bool value);
    void setBHasUnit(bool value);
    void setBHasBounds(int index, bool value);
    void setOther(modelEntity *value);
    void setVectorIsInitialized(bool value);
    void setBuildNode(ASTNode *value);
    void setTok(token *value);
    void setIsdt();
    void setName(const std::string name_arg);
    void setDesc(const std::string desc_arg);
    void setUnit(const std::string unit_arg);
    void setType(const int type_arg);
    void setSType(const std::string sType_arg);
    void setNType(const int nType_arg);
    void setDimType(const int dimType_arg);
	int setDims(const int dimval);

	// Get
    bool getBHasDesc() const;
    bool getBHasUnit() const;
    bool getBHasBounds(int index);
    modelEntity *getOther() const;
    bool getVectorIsInitialized() const;
    ASTNode *getBuildNode() const;
    token *getTok() const;
    bool checkIsdt();
    std::string getName();
    std::string getDesc();
    std::string getUnit();
    int geType();
    std::string getSType();
    int getNType();
    int getDimType();
    int getNumDims();
    int getMaxDims();
    void clearDims();
    std::string getGetMultiDimsFromSingle(int &index);
    int getDimsAt(int index);
    int getDimsCAt(int index) const;
    void setDummyIndex();
    modelEntity* ReturnObject();
	int setAllto(const double &val);

	// Virtual
    virtual int allocateArray(const double &val);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Parameter Class
class parameter : public modelEntity
{
public:
    parameter();
    ~parameter();

	//Set
	int allocateArray(const double &val);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variable Class 
class variable : public modelEntity
{
public:

	// Vector
	char* VLowerType;
	char* VUpperType;
	double* VUpper;
	double* VLower;
	char* VFixValueToggle;

	// Scalar
	char SUpperType;
	char SLowerType;
	double SUpper;
	double SLower;
	char SFixValueToggle;
	
public:
    variable();
    ~variable();

	//Vector operations
	int allocateArray(const double &val);

	//Setting allto
	int setAlltoB(const int &type, const char ctype, const double &dtype);

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object 
class object : public modelEntity
{
public:

	std::string sModelName;
    model* SModelObject;
    model* VModelObject;

public:
    object();
    ~object();

	void setModelName(std::string name);
	std::string getModelName();
    int setScalarObject(const model* mod);
    int allocateArray();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Model (Class stores the prototype of a model)
class model
{

    std::unordered_map<std::string, modelEntity*> ModelEntities;
	std::vector<ASTNode*> EquationNodes;
	std::vector<ASTNode*> InitNodes;

public:
    model();
    ~model();

    std::unordered_map<std::string, modelEntity*>* getModelEntities();
	std::vector<ASTNode*>* getAllEquationNodes();
	std::vector<ASTNode *>* getAllInitEquationNodes();
    bool insertModelEntity(std::string &symbolName, modelEntity* me);
    modelEntity* getModelEntity(model* first, std::string &symbolName);
	void insertEquationNode(ASTNode* EqNode);
	void insertInitNode(ASTNode* node);
};
