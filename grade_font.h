#ifndef _CLIMBLIB_GRADE_FONT_H_
#define _CLIMBLIB_GRADE_FONT_H_

/**
 * @file grade_font.h
 *
 * @brief Header that defines structures and methods for the Fontainebleau
 * grading system.
 */

#include <stddef.h>

/**
 * @brief Divisions that granulate difficulty within a grade
 */
typedef enum {
	/**
	 * @brief The "A" division
	 */
	GRADE_FONT_DIVISION_A,

	/**
	 * @brief The "B" division
	 */
	GRADE_FONT_DIVISION_B,

	/**
	 * @brief The "C" division
	 */
	GRADE_FONT_DIVISION_C,
} GradeFontainebleauDivision;

/**
 * @brief Modifier that indicates increased difficulty within a grade
 */
typedef enum {
	/**
	 * @brief No modifier present
	 */
	GRADE_FONT_MODIFIER_NONE,

	/**
	 * @brief The "+" modifier
	 */
	GRADE_FONT_MODIFIER_PLUS,
} GradeFontainebleauModifier;

/**
 * @brief A Fontainebleau grade.
 */
typedef struct {
	/**
	 * @brief The value of the grade.
	 */
	unsigned int grade;

	/**
	 * @brief The division of the grade.
	 */
	GradeFontainebleauDivision division;

	/**
	 * @brief The modifier of the grade.
	 */
	GradeFontainebleauModifier modifier;
} GradeFontainebleau;

/**
 * @brief Compares two @ref GradeFontainebleau instances.
 */
int GradeFontainebleau_cmp(const GradeFontainebleau, const GradeFontainebleau);

/**
 * @brief Produces a string representing the Fontainebleau grade.
 */
int GradeFontainebleau_str(const GradeFontainebleau, char *, size_t);

/**
 * @brief Populates a @ref GradeFontainebleau from a representative string.
 */
int GradeFontainebleau_fromstr(const char *, GradeFontainebleau *);

#endif
