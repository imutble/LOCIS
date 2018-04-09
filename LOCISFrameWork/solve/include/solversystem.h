#pragma once

#include "virtualinstruction.h"
#include "blockdecomposition.h"
#include "genericresidual.h"
#include "genericjacobian.h"

//solver specific includes
#include "solversundialskinsol.h"
#include "solversundialsida.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// encapsulates all information about a system of equations for the solverkernel
class solverSystem
{
    //direct
    solverSystem* daeInitSystem;
    int systemType;
    int solveMode;
    unsigned int numVar;
    unsigned int numEqu;
    std::vector<virtualOper>* pEquationVec; //direct mode
    genericResidual* residual;
    genericJacobian* jacobian;

    //time
    double tStart;
    double tEnd;
    unsigned int numSteps;

    //variables(Central)
    double* varx;
    double* varyy;
    double* varyp;

    //solver
    solver* solv;
    solverOptions* sops;
    solverOutput* sout;
    int numRoots;
    genericResidual* rootResidual;

    //block decomposition
    solverSystem* root;
    unsigned int blockId;
    unsigned int numBlocks;
    std::vector<solverSystem*> solveBlocks; //only the root node holds all the sub-blocks
    std::vector<unsigned int>* mapVarX;
    std::vector<unsigned int>* mapVarYY;
    std::vector<unsigned int>* mapVarYP;
    solverOptions* blockSopsNonLinAlg;
    solverOptions* blockSopsNonLinDae;
    int blockSolverNonLinAlg;
    int blockSolverNonLinDae;


public:
    solverSystem();
    ~solverSystem();

    //setter
    void setSystemType(int type);
    void setSolveMode(int mode);
    void setDaeInitSystem(solverSystem* daeInitSystem_arg);
    void setTimeRange(double tStart_arg, double tEnd_arg, unsigned int nSteps_arg);
    bool setAndAllocateSystemDims(unsigned int numVar_arg, unsigned int numEqu_arg);
    void setEquationVector(std::vector<virtualOper>* pEquationVec_arg);
    void setResidual(genericResidual* res);
    void setRootResidual(unsigned int numRoots_arg, genericResidual* rootResidual_arg);
    void setSolver(solver *solver_arg, solverOptions* sops_arg, solverOutput* sout_arg);
    void setBlockId(unsigned int blid);
    void setNumBlocks(unsigned int blnum);
    void addBlock(solverSystem* blsystem);
    void setBlockMapVarX(std::vector<unsigned int>* mapVarX_arg);
    void setBlockMapVarYY(std::vector<unsigned int>* mapVarYY_arg);
    void setBlockMapVarYP(std::vector<unsigned int>* mapVarYP_arg);
    void setBlockSolverOptionsNonLinAlg(solverOptions* bsops);
    void setBlockSolverOptionsNonLinDae(solverOptions* bsops);
    void setBlockSolverNonLinAlgName(int type);
    void setBlockSolverNonLinDaeName(int type);

    //getter
    solverSystem *getRoot();
    solverSystem* getDaeInitSystem();
    int getSystemType();
    int getSolveMode();
    unsigned int getNumVar();
    unsigned int getNumEqu();
    std::vector<virtualOper> *getPEquationVec();
    genericResidual* getResidual();
    genericJacobian* getJacobian();

    //time
    double getTStart();
    double getTEnd();
    unsigned int getNumSteps();

    double* getVarX();
    double* getVarYY();
    double* getVarYP();

    solver* getSolver();
    solverOptions* getSolverOptions();
    solverOutput* getSolverOutput();

    int getNumRoots();
    genericResidual* getRootResidual();

    unsigned int getBlockId();
    unsigned int getNumBlocks();
    solverSystem* getBlockAt(unsigned int id);
    solverOptions* getBlockSolverOptions();

    //logic
    solver* createBlockSolver(int systemType_arg, solverOptions *sops_arg, solverOutput *sout_arg);
    bool copyBlockVarXToRoot();
    bool copyBlockVarYYToRoot();
    bool copyBlockVarYPToRoot();

    void setVariables();
};
