from scipy.spatial.transform import Rotation as R
import numpy as np

def rotation_matrix_to_angle_axis(rotation_matrix):
    # Create a Rotation object from the rotation matrix
    rotation = R.from_matrix(rotation_matrix)

    # Convert to angle-axis representation
    angle_axis = rotation.as_rotvec()

    return angle_axis


def AngleAxisToRotationMatrix(rotvec):
    rotation = R.from_rotvec(rotvec)
    rotmat = rotation.as_matrix()
    return rotmat

# Example usage
rotation_matrix = np.array([
    [0.866, -0.5, 0],
    [0.5, 0.866, 0],
    [0, 0, 1]
])

angle_axis = rotation_matrix_to_angle_axis(rotation_matrix)
print("Angle-axis vector:", angle_axis)

if __name__ == '__main__':
    matrices = []
    matrices.append(np.array([
        [ 0.99999859, -0.00144998,  0.00085139],
        [ 0.00144729,  0.999994  ,  0.00314787],
        [-0.00085594, -0.00314663,  0.99999468]
    ]))
    matrices.append(np.array([
        [ 0.99999859,  0.00144729, -0.00085594],
        [-0.00144998,  0.999994  , -0.00314663],
        [ 0.00085139,  0.00314787,  0.99999468]
    ]))

    for rotmat in matrices:
        rotvec = rotation_matrix_to_angle_axis(rotmat)
        print(rotvec)


    rs2rotvec = np.array([0.0088916, -0.0166158, -0.00566794])
    # rs2rotvec = np.array([0.0135698, -0.0158088, -0.00747177])
    rotmat = AngleAxisToRotationMatrix(rs2rotvec)
    print(rotmat)