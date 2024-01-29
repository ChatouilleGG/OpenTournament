// Copyright (c) 2019-2020 Open Tournament Project, All Rights Reserved.

/////////////////////////////////////////////////////////////////////////////////////////////////

#include "SUR_LoadingScreenWidget.h"
#include "SlateOptMacros.h"

#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"
#include "Widgets/Images/SImage.h"
#include "Engine/Texture2D.h"

#include "UR_WorldSettings.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SUR_LoadingScreenWidget::Construct(const FArguments& InArgs)
{
    FString MapName = InArgs._MapName;
    FString MapDescription;

    FMapInfo MapInfo;
    bool bFoundThumbnail = false;
    if (AUR_WorldSettings::GetMapInfoFromPath(MapName, MapInfo))
    {
        MapName = MapInfo.DisplayName;
        MapDescription = MapInfo.Description;
        if (!MapInfo.Thumbnail.IsNull())
        {
            if (UTexture2D* Tex = MapInfo.Thumbnail.LoadSynchronous())
            {
                ThumbnailBrush = FDeferredCleanupSlateBrush::CreateBrush(Tex);
                bFoundThumbnail = true;
            }
        }
    }

    if (!bFoundThumbnail)
    {
        //TODO: provide a fallback image
        ThumbnailBrush = FDeferredCleanupSlateBrush::CreateBrush(*FAppStyle::GetDefaultBrush());
    }

	ChildSlot
	[
        // full screen box with centered contents
        SNew(SBorder)
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Center)
        [
            // Vertical box
            SNew(SVerticalBox)

            // Slot 1 = title "Loading"
            + SVerticalBox::Slot()
            .HAlign(HAlign_Center)
            .Padding(FMargin(0,0,0,100))
            [
                SNew(STextBlock)
                .TextStyle(FCoreStyle::Get(), "EmbossedText")
                .ColorAndOpacity(FSlateColor(FLinearColor::White))
                .Text(FText::FromString("SlateLoadingTest"))
            ]

            // Slot 2 = throbber
            + SVerticalBox::Slot()
            .HAlign(HAlign_Center)
            [
                SNew(SThrobber)
            ]

            // Slot 3 = map name
            + SVerticalBox::Slot()
            .HAlign(HAlign_Fill)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .FillWidth(1)
                .HAlign(HAlign_Right)
                .Padding(10)
                [
                    SNew(STextBlock)
                    .ColorAndOpacity(FSlateColor(FLinearColor::White))
                    .Text(FText::FromString("MapName"))
                ]
                + SHorizontalBox::Slot()
                .FillWidth(1)
                .Padding(10)
                [
                    SNew(STextBlock)
                    .ColorAndOpacity(FSlateColor(FLinearColor::White))
                    .Text(FText::FromString(MapName))
                ]
            ]

            // Slot 4 = map description
            + SVerticalBox::Slot()
            .HAlign(HAlign_Fill)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .FillWidth(1)
                .HAlign(HAlign_Right)
                .Padding(10)
                [
                    SNew(STextBlock)
                    .ColorAndOpacity(FSlateColor(FLinearColor::White))
                    .Text(FText::FromString("Description"))
                ]
                + SHorizontalBox::Slot()
                .FillWidth(1)
                .Padding(10)
                [
                    SNew(STextBlock)
                    .ColorAndOpacity(FSlateColor(FLinearColor::White))
                    .Text(FText::FromString(MapDescription))
                ]
            ]

            // Slot 5 = map thumbnail
            + SVerticalBox::Slot()
            .HAlign(HAlign_Fill)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .FillWidth(1)
                .HAlign(HAlign_Right)
                .Padding(10)
                [
                    SNew(STextBlock)
                    .ColorAndOpacity(FSlateColor(FLinearColor::White))
                    .Text(FText::FromString("Thumbnail"))
                ]
                + SHorizontalBox::Slot()
                .FillWidth(1)
                .HAlign(HAlign_Left)
                .Padding(10)
                [
                    SNew(SImage)
                    .Image(ThumbnailBrush->GetSlateBrush())
                    .DesiredSizeOverride(FVector2D(148,148))
                ]
            ]
        ]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

/*

FSlateBrush UWidgetBlueprintLibrary::MakeBrushFromTexture(UTexture2D* Texture, int32 Width, int32 Height)
{
    if ( Texture )
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(Texture);
        Width = (Width > 0) ? Width : Texture->GetSizeX();
        Height = (Height > 0) ? Height : Texture->GetSizeY();
        Brush.ImageSize = FVector2D(Width, Height);
        return Brush;
    }

    return FSlateNoResource();
}
*/
