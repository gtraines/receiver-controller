import math

def camera_ground_point(
    lat, lon,
    heading_deg,
    gimbal_yaw_deg, gimbal_pitch_deg, gimbal_roll_deg,
    altitude_m,
):
    """
    Calculates the ground point (latitude, longitude) the camera is looking at.

    Parameters:
        lat (float): Aircraft latitude in degrees
        lon (float): Aircraft longitude in degrees
        heading_deg (float): Aircraft heading in degrees (N=0, E=90)
        gimbal_yaw_deg (float): Gimbal yaw relative to aircraft nose, in degrees (right = +)
        gimbal_pitch_deg (float): Gimbal pitch (down from horizontal = +), in degrees
        gimbal_roll_deg (float): Gimbal roll (unused here), in degrees
        altitude_m (float): Altitude of the camera above ground in meters (REQUIRED)

    Returns:
        (lat, lon): Tuple of latitude and longitude of ground intersection
    """
    # Convert all angles to radians
    heading = math.radians(heading_deg)
    yaw = math.radians(gimbal_yaw_deg)
    pitch = math.radians(gimbal_pitch_deg)
    # Total pan angle from North (aircraft heading + gimbal yaw)
    total_yaw = heading + yaw

    # Prevent divide by zero; camera pointing exactly horizontal, ground intersection is at infinity.
    if math.cos(pitch) == 0:
        return None

    ground_dist = altitude_m * math.tan(math.pi/2 + pitch)  # pitch = -90deg => 0 distance (nadir)

    # Calculate offset in north and east due to yaw
    dn = ground_dist * math.cos(total_yaw)  # north offset in meters
    de = ground_dist * math.sin(total_yaw)  # east offset in meters

    # Convert meters to lat/lon deltas (approximation)
    dlat = dn / 111320  # meters per degree latitude
    dlon = de / (40075000 * math.cos(math.radians(lat)) / 360)

    target_lat = lat + dlat
    target_lon = lon + dlon

    return target_lat, target_lon

# Example Usage:
# Aircraft at (37.0, -122.0), heading 45deg, gimbal looking right (90 deg yaw), 45 deg down, altitude 120m
target = camera_ground_point(
    37.0, -122.0,
    heading_deg=45,
    gimbal_yaw_deg=90,
    gimbal_pitch_deg=-45,
    gimbal_roll_deg=0,
    altitude_m=120
)
print(target)
