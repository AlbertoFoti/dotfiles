using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LanderScript : MonoBehaviour
{
    public float radialPosition;
    public float longitude;
    public float latitude;

    // Start is called before the first frame update
    void Start()
    {
        radialPosition = 250.00;
        longitude = 0.00;
        latitude = 0.00;
    }

    // Update is called once per frame
    void Update()
    {
        float x = radialPosition * Mathf.Cos(longitude) * Mathf.Sin(latitude);
        float y = radialPosition * Mathf.Sin(longitude) * Mathf.Sin(latitude);
        float z = radialPosition * Mathf.Cos(latitude); 

        transform.position = new Vector3(x, y, z);       
    }
}
