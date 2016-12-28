// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct FUtil
{
	static FORCEINLINE float SignedAngle2D(const FVector2D& A, const FVector2D& B)
	{
		return FMath::RadiansToDegrees(atan2(FVector2D::CrossProduct(A, B), FVector2D::DotProduct(A, B)));
	}

	static FORCEINLINE float Angle2D(const FVector2D& A, const FVector2D& B)
	{
		return FMath::RadiansToDegrees(acos(FVector2D::DotProduct(A, B)));
	}
};
