using UnityEngine;
using System.Collections;

public class barControl : MonoBehaviour {

	private GameObject director;
	private GameObject player;

	private Transform gravity;
	private Transform anti;
	//private float massToUse; 
	private float scaler;

	// Use this for initialization
	void Start () {
		Debug.Log ("OMG");
	}
	
	// Update is called once per frame
	void Update () {
	
		//massToUse = gameObject.GetComponent<planet> ().mass;
		scaler = gameObject.GetComponent<planet> ().mass / 4.0f ;

		gravity = transform.Find("GravityDisplay");
		anti = transform.Find ("AntiGravityDisplay");

		foreach (Transform childs in gameObject.GetComponent<planet>().transform)
		{
			if(gameObject.GetComponent<planet> ().mass > 0)
			{

			Debug.Log (childs.transform.localScale);
				//childs.transform.healthBar.renderer.material.color = Color.grey;
				gravity.transform.localScale = new Vector3 (scaler *(50.0f), 1.0f*(50.0f), 1.0f);
				anti.transform.localScale = new Vector3 (0, 0, 0);
			}
			else 
			{
				//temp.transform.renderer.material.color = Color.yellow;
				anti.transform.localScale = new Vector3 ((-1.0f)*scaler*(50.0f), 1.0f*(50.0f), 1.0f);
				gravity.transform.localScale = new Vector3 (0, 0, 0);
			}
		}

		/*foreach (Transform AntiGravityDisplay in gameObject.GetComponent<planet>().transform)
		{
			if(gameObject.GetComponent<planet> ().mass < 0)
			{
				Debug.Log (AntiGravityDisplay.transform.localScale);
				AntiGravityDisplay.transform.localScale = new Vector3 ((-1.0f)*scaler, 1.0f, 1.0f);
			}
			else 
			{
				AntiGravityDisplay.transform.localScale = new Vector3 (0, 0, 0);
			}


			//ui_healthBar.transform.localPosition = new Vector3 (scaler, 0, 0);
			// do whatever you want with child transform object here
		}*/
	}
}
