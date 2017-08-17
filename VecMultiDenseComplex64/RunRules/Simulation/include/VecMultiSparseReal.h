/**\file */
#ifndef SLIC_DECLARATIONS_VecMultiSparseReal_H
#define SLIC_DECLARATIONS_VecMultiSparseReal_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define VecMultiSparseReal_PCIE_ALIGNMENT (16)


/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] param_m Interface Parameter "m".
 * \param [in] param_n Interface Parameter "n".
 * \param [in] param_original_m Interface Parameter "original_m".
 * \param [in] instream_coefficients The stream should be of size (param_n * 4) bytes.
 * \param [in] instream_exponents The stream should be of size (param_n * 4) bytes.
 * \param [in] instream_padded_xs The stream should be of size 2048 bytes.
 * \param [in] instream_xs The stream should be of size (param_m * 4) bytes.
 * \param [out] outstream_result The stream should be of size (param_m * 4) bytes.
 */
void VecMultiSparseReal(
	uint32_t param_m,
	uint32_t param_n,
	uint32_t param_original_m,
	const float *instream_coefficients,
	const uint32_t *instream_exponents,
	const float *instream_padded_xs,
	const float *instream_xs,
	float *outstream_result);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_m Interface Parameter "m".
 * \param [in] param_n Interface Parameter "n".
 * \param [in] param_original_m Interface Parameter "original_m".
 * \param [in] instream_coefficients The stream should be of size (param_n * 4) bytes.
 * \param [in] instream_exponents The stream should be of size (param_n * 4) bytes.
 * \param [in] instream_padded_xs The stream should be of size 2048 bytes.
 * \param [in] instream_xs The stream should be of size (param_m * 4) bytes.
 * \param [out] outstream_result The stream should be of size (param_m * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *VecMultiSparseReal_nonblock(
	uint32_t param_m,
	uint32_t param_n,
	uint32_t param_original_m,
	const float *instream_coefficients,
	const uint32_t *instream_exponents,
	const float *instream_padded_xs,
	const float *instream_xs,
	float *outstream_result);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	uint32_t param_m; /**<  [in] Interface Parameter "m". */
	uint32_t param_n; /**<  [in] Interface Parameter "n". */
	uint32_t param_original_m; /**<  [in] Interface Parameter "original_m". */
	const float *instream_coefficients; /**<  [in] The stream should be of size (param_n * 4) bytes. */
	const uint32_t *instream_exponents; /**<  [in] The stream should be of size (param_n * 4) bytes. */
	const float *instream_padded_xs; /**<  [in] The stream should be of size 2048 bytes. */
	const float *instream_xs; /**<  [in] The stream should be of size (param_m * 4) bytes. */
	float *outstream_result; /**<  [out] The stream should be of size (param_m * 4) bytes. */
} VecMultiSparseReal_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void VecMultiSparseReal_run(
	max_engine_t *engine,
	VecMultiSparseReal_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *VecMultiSparseReal_run_nonblock(
	max_engine_t *engine,
	VecMultiSparseReal_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void VecMultiSparseReal_run_group(max_group_t *group, VecMultiSparseReal_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *VecMultiSparseReal_run_group_nonblock(max_group_t *group, VecMultiSparseReal_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void VecMultiSparseReal_run_array(max_engarray_t *engarray, VecMultiSparseReal_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *VecMultiSparseReal_run_array_nonblock(max_engarray_t *engarray, VecMultiSparseReal_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* VecMultiSparseReal_convert(max_file_t *maxfile, VecMultiSparseReal_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* VecMultiSparseReal_init(void);

/* Error handling functions */
int VecMultiSparseReal_has_errors(void);
const char* VecMultiSparseReal_get_errors(void);
void VecMultiSparseReal_clear_errors(void);
/* Free statically allocated maxfile data */
void VecMultiSparseReal_free(void);
/* returns: -1 = error running command; 0 = no error reported */
int VecMultiSparseReal_simulator_start(void);
/* returns: -1 = error running command; 0 = no error reported */
int VecMultiSparseReal_simulator_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_VecMultiSparseReal_H */

