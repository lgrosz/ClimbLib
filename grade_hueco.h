#ifndef _CLIMBLIB_GRADE_HUECO_H_
#define _CLIMBLIB_GRADE_HUECO_H_

/**
 * @file grade_hueco.h
 *
 * @brief Header that defines structures and methods for the Hueco grading
 * system (V-scale).
 */

#include <stddef.h>

/**
 * @brief Modifiers that granulate difficulty within a grade
 */
typedef enum {
	/**
	 * @brief The "-" modifier
	 */
	GRADE_HUECO_MODIFIER_MINUS,

	/**
	 * @brief No modifier present
	 */
	GRADE_HUECO_MODIFIER_NONE,

	/**
	 * @brief The "+" modifier
	 */
	GRADE_HUECO_MODIFIER_PLUS,
} GradeHuecoModifier;

/**
 * @brief A Hueco grade.
 */
typedef struct {
	/**
	 * @brief The value of the grade.
	 */
	unsigned int grade;

        /**
         * @brief A modifier to refine the grade.
         */
        GradeHuecoModifier modifier;
} GradeHueco;

/**
 * @brief Compares two @ref GradeHueco instances.
 */
int GradeHueco_cmp(const GradeHueco, const GradeHueco);

/**
 * @brief Produces a string representing the Hueco grade.
 */
int GradeHueco_str(const GradeHueco, char *, size_t);

/**
 * @brief Populates a @ref GradeHueco from a representative string.
 */
int GradeHueco_fromstr(const char *, GradeHueco *);

#endif
