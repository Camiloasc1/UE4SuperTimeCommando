// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct GUtil
{
	static FORCEINLINE float SignedAngle2D(const FVector& A, const FVector& B)
	{
		return SignedAngle2D(FVector2D(A), FVector2D(B));
	}

	static FORCEINLINE float SignedAngle2D(const FVector2D& A, const FVector2D& B)
	{
		FVector2D An = A.GetSafeNormal();
		FVector2D Bn = B.GetSafeNormal();
		return FMath::RadiansToDegrees(atan2(FVector2D::CrossProduct(An, Bn), FVector2D::DotProduct(An, Bn)));
	}

	static FORCEINLINE float Angle2D(const FVector& A, const FVector& B)
	{
		return Angle2D(FVector2D(A), FVector2D(B));
	}

	static FORCEINLINE float Angle2D(const FVector2D& A, const FVector2D& B)
	{
		FVector2D An = A.GetSafeNormal();
		FVector2D Bn = B.GetSafeNormal();
		return FMath::RadiansToDegrees(acos(FVector2D::DotProduct(An, Bn)));
	}
};
