// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct FUtil
{
	static FORCEINLINE float SignedAngle2D(const FVector2D& A, const FVector2D& B)
	{
		FVector2D An = A.GetSafeNormal();
		FVector2D Bn = B.GetSafeNormal();
		return FMath::RadiansToDegrees(atan2(FVector2D::CrossProduct(An, Bn), FVector2D::DotProduct(An, Bn)));
	}

	static FORCEINLINE float Angle2D(const FVector2D& A, const FVector2D& B)
	{
		FVector2D An = A.GetSafeNormal();
		FVector2D Bn = B.GetSafeNormal();
		return FMath::RadiansToDegrees(acos(FVector2D::DotProduct(An, Bn)));
	}
};
