#include "grade_item.h"
#include "allocator.h"
#include "grade_font.h"

struct GradeItem {
	GradeItemType type;
	union {
		GradeFontainebleau fontainebleau;
		GradeHueco hueco;
	} grade;
	GradeItem *next;
};

static GradeItem *GradeItem_new()
{
	GradeItem *grade_item;

	if ((grade_item = climblib_malloc(sizeof(GradeItem)))) {
		grade_item->next = NULL;
	}

	return grade_item;
}

GradeItem *GradeItem_new_fontainebleau(GradeFontainebleau grade_fontainebleau)
{
	GradeItem *grade_item;

	if ((grade_item = GradeItem_new())) {
		grade_item->type = GradeItemType_Fontainebleau;
		grade_item->grade.fontainebleau = grade_fontainebleau;
	}

	return grade_item;
}

GradeItem *GradeItem_new_hueco(GradeHueco grade_hueco)
{
	GradeItem *grade_item;

	if ((grade_item = GradeItem_new())) {
		grade_item->type = GradeItemType_Hueco;
		grade_item->grade.hueco = grade_hueco;
	}

	return grade_item;
}

int GradeItem_fontainebleau(GradeItem *grade_item, GradeFontainebleau *grade_fontainebleau)
{
	if (grade_item->type == GradeItemType_Fontainebleau) {
		*grade_fontainebleau = grade_item->grade.fontainebleau;
		return 0;
	}

	return 1;
}

int GradeItem_hueco(GradeItem *grade_item, GradeHueco *grade_hueco)
{
	if (grade_item->type == GradeItemType_Hueco) {
		*grade_hueco = grade_item->grade.hueco;
		return 0;
	}

	return 1;
}

void GradeItem_free(GradeItem *grade_item)
{
	if (grade_item)	climblib_free(grade_item);
}

GradeItem *GradeItem_set_next(GradeItem *grade_item, GradeItem *next_item)
{
	GradeItem *previous_item;

	previous_item = grade_item->next;
	grade_item->next = next_item;

	return previous_item;
}

GradeItem *GradeItem_next(GradeItem *grade_item)
{
	return grade_item->next;
}
