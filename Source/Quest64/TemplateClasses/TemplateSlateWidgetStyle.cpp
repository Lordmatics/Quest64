// Start 28/12/2018 - Niall Maple & Dane Maple

#include "TemplateSlateWidgetStyle.h"

FTemplateSlateStyle::FTemplateSlateStyle()
{
}

FTemplateSlateStyle::~FTemplateSlateStyle()
{
}

const FName FTemplateSlateStyle::TypeName(TEXT("FTemplateSlateStyle"));

const FTemplateSlateStyle& FTemplateSlateStyle::GetDefault()
{
	static FTemplateSlateStyle Default;
	return Default;
}

void FTemplateSlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

