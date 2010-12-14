#include "TC_COPASI_api.h"

tc_matrix (*_tc_simulateDeterministic)(double startTime, double endTime, int numSteps) = 0;
tc_matrix (*_tc_simulateStochastic)(double startTime, double endTime, int numSteps) = 0;
tc_matrix (*_tc_simulateHybrid)(double startTime, double endTime, int numSteps) = 0;
tc_matrix (*_tc_simulateTauLeap)(double startTime, double endTime, int numSteps) = 0;
tc_matrix (*_tc_getSteadyState)() = 0;
tc_matrix (*_tc_steadyStateScan)(const char * param, double start, double end, int numSteps) = 0;
tc_matrix (*_tc_steadyStateScan2D)(const char * param1, double start1, double end1, int numSteps1,const char * param2, double start2, double end2, int numSteps2) = 0;
tc_matrix (*_tc_getJacobian)() = 0;
tc_matrix (*_tc_getEigenvalues)() = 0;
tc_matrix (*_tc_getUnscaledElasticities)() = 0;
tc_matrix (*_tc_getUnscaledConcentrationCC)() = 0;
tc_matrix (*_tc_getUnscaledFluxCC)() = 0;
tc_matrix (*_tc_getScaledElasticities)() = 0;
tc_matrix (*_tc_getScaledConcentrationCC)() = 0;
tc_matrix (*_tc_getScaledFluxCC)() = 0;

tc_matrix tc_simulateDeterministic(double startTime, double endTime, int numSteps)
{
	if (_tc_simulateDeterministic)
		return _tc_simulateDeterministic(startTime, endTime, numSteps);
	return tc_createMatrix(0,0);
}

tc_matrix tc_simulateStochastic(double startTime, double endTime, int numSteps)
{
	if (_tc_simulateStochastic)
		return _tc_simulateStochastic(startTime, endTime, numSteps);
	return tc_createMatrix(0,0);
}

tc_matrix tc_simulateHybrid(double startTime, double endTime, int numSteps)
{
	if (_tc_simulateHybrid)
		return _tc_simulateHybrid(startTime, endTime, numSteps);
	return tc_createMatrix(0,0);
}

tc_matrix tc_simulateTauLeap(double startTime, double endTime, int numSteps)
{
	if (_tc_simulateTauLeap)
		return _tc_simulateTauLeap(startTime, endTime, numSteps);
	return tc_createMatrix(0,0);
}

tc_matrix tc_getSteadyState()
{
	if (_tc_getSteadyState)
		return _tc_getSteadyState();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getJacobian()
{
	if (_tc_getJacobian)
		return _tc_getJacobian();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getEigenvalues()
{
	if (_tc_getEigenvalues)
		return _tc_getEigenvalues();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getUnscaledElasticities()
{
	if (_tc_getUnscaledElasticities)
		return _tc_getUnscaledElasticities();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getUnscaledConcentrationCC()
{
	if (_tc_getUnscaledConcentrationCC)
		return _tc_getUnscaledConcentrationCC();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getUnscaledFluxCC()
{
	if (_tc_getUnscaledFluxCC)
		return _tc_getUnscaledFluxCC();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getScaledElasticities()
{
	if (_tc_getScaledElasticities)
		return _tc_getScaledElasticities();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getScaledConcentrationCC()
{
	if (_tc_getScaledConcentrationCC)
		return _tc_getScaledConcentrationCC();
	return tc_createMatrix(0,0);
}

tc_matrix tc_getScaledFluxCC()
{
	if (_tc_getScaledFluxCC)
		return _tc_getScaledFluxCC();
	return tc_createMatrix(0,0);
}

tc_matrix tc_steadyStateScan(const char * param, double start, double end, int numSteps)
{
	if (_tc_steadyStateScan)
		return _tc_steadyStateScan(param, start, end, numSteps);
	return tc_createMatrix(0,0);
}

tc_matrix tc_steadyStateScan2D(const char * param1, double start1, double end1, int numSteps1,
																			const char * param2, double start2, double end2, int numSteps2)
{
	if (_tc_steadyStateScan2D)
		return _tc_steadyStateScan2D(param1, start1, end1, numSteps1, param1, start2, end2, numSteps2);
	return tc_createMatrix(0,0);
}

void tc_COPASI_api( 
tc_matrix (*simulateDeterministic)(double startTime, double endTime, int numSteps),
tc_matrix (*simulateStochastic)(double startTime, double endTime, int numSteps),
tc_matrix (*simulateHybrid)(double startTime, double endTime, int numSteps),
tc_matrix (*simulateTauLeap)(double startTime, double endTime, int numSteps),
tc_matrix (*getSteadyState)(),
tc_matrix (*steadyStateScan)(const char * param, double start, double end, int numSteps),
tc_matrix (*steadyStateScan2D)(const char * param1, double start1, double end1, int numSteps1,const char * param2, double start2, double end2, int numSteps2),
tc_matrix (*getJacobian)(),
tc_matrix (*getEigenvalues)(),
tc_matrix (*getUnscaledElasticities)(),
tc_matrix (*getUnscaledConcentrationCC)(),
tc_matrix (*getUnscaledFluxCC)(),
tc_matrix (*getScaledElasticities)(),
tc_matrix (*getScaledConcentrationCC)(),
tc_matrix (*getScaledFluxCC)()
)
{
	_tc_simulateDeterministic = simulateDeterministic;
	_tc_simulateStochastic = simulateStochastic;
	_tc_simulateHybrid = simulateHybrid;
	_tc_simulateTauLeap = simulateTauLeap;
	_tc_getSteadyState = getSteadyState;
	_tc_getJacobian = getJacobian;
	_tc_getEigenvalues = getEigenvalues;
	_tc_getUnscaledElasticities = getUnscaledElasticities;
	_tc_getUnscaledConcentrationCC = getUnscaledConcentrationCC;
	_tc_getUnscaledFluxCC = getUnscaledFluxCC;
	_tc_getScaledElasticities = getScaledElasticities;
	_tc_getScaledConcentrationCC = getScaledConcentrationCC;
	_tc_getScaledFluxCC = getScaledFluxCC;
	_tc_steadyStateScan = steadyStateScan;
	_tc_steadyStateScan2D = steadyStateScan2D;
}

