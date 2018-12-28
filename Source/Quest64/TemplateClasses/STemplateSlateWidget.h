// Start 28/12/2018 - Niall Maple & Dane Maple

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class QUEST64_API STemplateSlateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STemplateSlateWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
