#include "calibrator.hpp"

#include "DEBUG_reference_profile.hpp"

calibrator::ReferenceProfile Calibrator::getReferenceProfile() const{
    return calibrator::DEBUG_referenceProfile;
}