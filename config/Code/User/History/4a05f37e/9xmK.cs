using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LanderScript : MonoBehaviour
{
    public float radialPosition;
    public float longitude;
    public float latitude;

    private List<Vector3> trajectoryPoints; // List to store trajectory points
    private int currentPointIndex; // Index of the current point in the trajectory


    // Start is called before the first frame update
    void Start()
    {
        trajectoryPoints = new List<Vector3>();
        currentPointIndex = 0;

        // Read trajectory data from file
        ReadTrajectoryFromFile();
    }

    // Update is called once per frame
    void Update()
    {
        float x = radialPosition * Mathf.Cos(longitude) * Mathf.Sin(latitude);
        float z = radialPosition * Mathf.Sin(longitude) * Mathf.Sin(latitude);
        float y = radialPosition * Mathf.Cos(latitude); 

        transform.position = new Vector3(x, y, z);       
    }
}
