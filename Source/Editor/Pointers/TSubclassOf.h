#pragma once
#include <type_traits>

// Forward declaration of UClass
class UClass;

// Template class representing a subclass of a given base class
template<typename BaseClass>
class TSubclassOf
{
public:
    // Default constructor
    TSubclassOf() : Class(nullptr) {}

    // Construct from UClass pointer
    explicit TSubclassOf(UClass* InClass) : Class(InClass) {}

    // Conversion operator to UClass pointer
    operator UClass* () const { return Class; }

    // Comparison operators
    bool operator==(const TSubclassOf& Other) const { return Class == Other.Class; }
    bool operator!=(const TSubclassOf& Other) const { return Class != Other.Class; }

private:
    // Pointer to the UClass representing the subclass
    UClass* Class;
};