#include "calibrator.hpp"

#include "DEBUG_reference_profile.hpp"

#include "calibrator_constants.hpp"

calibrator::ReferenceProfile Calibrator::getReferenceProfile() const{
    return calibrator::DEBUG_referenceProfilePrinterRGB;
}