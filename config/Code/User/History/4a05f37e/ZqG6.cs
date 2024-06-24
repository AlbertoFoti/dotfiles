using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LanderScript : MonoBehaviour
{
    public float radialPosition;
    public float longitude;
    public float latitude;

    public float movementSpeed;

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

        if (trajectoryPoints.Count > 0 && currentPointIndex < trajectoryPoints.Count)
        {
            // Move towards the current point
            transform.position = Vector3.MoveTowards(transform.position, trajectoryPoints[currentPointIndex], movementSpeed * Time.deltaTime);

            // Check if reached the current point
            if (Vector3.Distance(transform.position, trajectoryPoints[currentPointIndex]) < 0.1f)
            {
                currentPointIndex++;

                // Call function on LanderScript object (if it exists)
                if (landerScriptObject != null)
                {
                    landerScriptObject.SendMessage("OnPointReached", SendMessageOptions.DontRequireReceiver);
                }
            }
        }
        float x = radialPosition * Mathf.Cos(longitude) * Mathf.Sin(latitude);
        float z = radialPosition * Mathf.Sin(longitude) * Mathf.Sin(latitude);
        float y = radialPosition * Mathf.Cos(latitude); 

        transform.position = new Vector3(x, y, z);       
    }
}
