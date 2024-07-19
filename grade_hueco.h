#ifndef _CLIMBLIB_GRADE_HUECO_H_
#define _CLIMBLIB_GRADE_HUECO_H_

/**
 * @file grade_hueco.h
 *
 * @brief Header that defines structures and methods for the Hueco grading
 * system (V-scale).
 *
 * @details
 * The Hueco grading system (often called the V-Scale after its developer John
 * "The Verm" Shermin) is an open ended grading scale. It was developed during
 * the publishing of John Shermin's guidebook for Hueco Tanks, TX, USA.
 * Famously, the developer of this grading system condemns its use.
 *
 * Prefixed, by "V," the scale is defined by positive integers. As the integers
 * rise the perceived difficulty increases. Sometimes a "+" or "-" postfix is
 * adding to further refine grade within a describing integer.
 *
 * There is little, besides community consensus, that defines how much
 * difficulty consititutes a increment of a grade.
 */

#include <stddef.h>

/**
 * @brief Modifiers that granulate difficulty within a grade
 *
 * @details
 * These modifiers, when present, add more granuarity with a given grade. These
 * modifiers are indicated with a "+" or "-" postfixing the grade. Intuitively,
 * a "-" means the difficulty is on the easier end of the grade while a "+"
 * indicates it's on the opposite.
 *
 * The enumerations are ordered such that @ref GRADE_HUECO_MODIFIER_MINUS is
 * logically less then @ref GRADE_HUECO_MODIFIER_NONE and @ref
 * GRADE_HUECO_MODIFIER_NONE is logically less than @ref
 * GRADE_HUECO_MODIFIER_PLUS.
 */
typedef enum {
	/**
	 * @brief The "-" modifier
	 *
	 * @details
	 * Indicates the difficulty is on the lower-end of the grade.
	 */
	GRADE_HUECO_MODIFIER_MINUS,

	/**
	 * @brief No modifier present
	 *
	 * @details
	 * Indicates nothing about where the difficulty is in the grade-range.
	 */
	GRADE_HUECO_MODIFIER_NONE,

	/**
	 * @brief The "+" modifier
	 *
	 * @details
	 * Indicates the difficulty is on the upper-end of the grade.
	 */
	GRADE_HUECO_MODIFIER_PLUS,
} GradeHuecoModifier;

/**
 * @brief A Hueco grade.
 *
 * @details
 * A Hueco grade is composed of two parts: 1. the value; 2. an optional modifier.
 */
typedef struct {
	/**
	 * @brief The value of the grade.
	 *
	 * @details
	 * The value of the grade is a unsigned integer, as by definition the
	 * grade range begins at zero, inclusive, and has no maximum.
	 */
	unsigned int grade;

        /**
         * @brief A modifier to refine the grade.
         *
         * @details
         * Refines the difficulty represented by the grade. Conceptually, this
         * value is optional. In practice, a values of @ref
         * GRADE_HUECO_MODIFIER_NONE indicates the lack of a modifier.
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
