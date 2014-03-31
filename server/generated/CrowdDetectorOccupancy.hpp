/* Autogenerated with Kurento Idl */

#ifndef __CROWD_DETECTOR_OCCUPANCY_HPP__
#define __CROWD_DETECTOR_OCCUPANCY_HPP__

#include <jsoncpp/json/json.h>
#include <JsonRpcException.hpp>
#include <memory>

#include "Media.hpp"

class JsonSerializer;

namespace kurento {
class CrowdDetectorOccupancy;
} /* kurento */

void Serialize(kurento::CrowdDetectorOccupancy& event, JsonSerializer& s);

namespace kurento {

class CrowdDetectorOccupancy : public virtual Media
{

public:

  CrowdDetectorOccupancy (float occupancyPercentage, int occupancyLevel, const std::string& roiID, std::shared_ptr<MediaObject> source, const std::string& type) : Media (source, type) {
    this->occupancyPercentage = occupancyPercentage;
    this->occupancyLevel = occupancyLevel;
    this->roiID = roiID;
  };

  CrowdDetectorOccupancy (const Json::Value &value);

  virtual void setOccupancyPercentage (float occupancyPercentage) {
    this->occupancyPercentage = occupancyPercentage;
  };

  virtual float getOccupancyPercentage () {
    return occupancyPercentage;
  };

  virtual void setOccupancyLevel (int occupancyLevel) {
    this->occupancyLevel = occupancyLevel;
  };

  virtual int getOccupancyLevel () {
    return occupancyLevel;
  };

  virtual void setRoiID (std::string roiID) {
    this->roiID = roiID;
  };

  virtual const std::string& getRoiID () {
    return roiID;
  };

  static std::string getName() {
    return "CrowdDetectorOccupancy";
  }

protected:

  CrowdDetectorOccupancy() {};

private:
  float occupancyPercentage;
  int occupancyLevel;
  std::string roiID;

  friend void ::Serialize(CrowdDetectorOccupancy& event, JsonSerializer& s);
};

} /* kurento */

#endif /*  __CROWD_DETECTOR_OCCUPANCY_HPP__ */