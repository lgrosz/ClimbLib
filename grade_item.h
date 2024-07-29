#ifndef _CLIMBLIB_GRADE_ITEM_H_
#define _CLIMBLIB_GRADE_ITEM_H_

#include "grade_font.h"
#include "grade_hueco.h"

/**
 * @file grade_item.h
 *
 * @brief Provides an abstraction for grades.
 */

/**
 * @brief Grade item type.
 */
typedef enum {
	GradeItemType_Fontainebleau,
	GradeItemType_Hueco,
} GradeItemType;

/**
 * @brief A grade item.
 */
typedef struct GradeItem GradeItem;

/**
 * @brief Create a new fontainebleau grade type.
 */
GradeItem *GradeItem_new_fontainebleau(GradeFontainebleau);

/**
 * @brief Create a new hueco grade type.
 */
GradeItem *GradeItem_new_hueco(GradeHueco);

/**
 * @brief Gives back the grade item type.
 */
GradeItemType GradeItem_type(GradeItem *);

/**
 * @brief Gives back the hueco grade of the item.
 *
 * @returns 0 on success, non-zero otherwise.
 */
int GradeItem_fontainebleau(GradeItem *, GradeFontainebleau *);

/**
 * @brief Gives back the hueco grade of the item.
 *
 * @returns 0 on success, non-zero otherwise.
 */
int GradeItem_hueco(GradeItem *, GradeHueco *);

/**
 * @brief Frees a grade item.
 */
void GradeItem_free(GradeItem *);

#endif
