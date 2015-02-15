using UnityEngine;
using System.Collections;

public class magnet : MonoBehaviour {

	private GameObject director;
	private GameObject player;

	private Vector3 magnetPosition; 
	private Vector3 magnetForce;

	private float lifeSpan;

	// Use this for initialization
	void Start () {
		director = GameObject.FindGameObjectWithTag ("Director");
		player = director.GetComponent<GameDirector>().player;
		magnetPosition = gameObject.transform.position; 
		lifeSpan = 0;

	}
	
	// Update is called once per frame
	void Update () {
		lifeSpan += Time.deltaTime;
		if (lifeSpan >= 5.0f ){
			killItself();
		}
	}

	public void magnetOn(){
		Debug.Log ("1");
		magnetForce = 100 * (magnetPosition - player.transform.position);
		player.transform.forward = Vector3.Normalize (magnetForce);
		player.GetComponent<playerBehavior>().playerForce = Vector3.Magnitude (magnetForce);
				
				
	}

	void OnTriggerEnter(Collider col){
		magnetForce = 0 * (magnetPosition - player.transform.position);
		player.transform.forward = Vector3.Normalize(magnetForce );
		player.GetComponent<playerBehavior>().playerForce = Vector3.Magnitude (magnetForce );
	}

	void killItself(){
		Vector3 dist = getDist (player.transform.position, transform.position);
		if( Vector3.Magnitude(dist) > 10.0f ){
			Destroy (gameObject);
		}else{
			lifeSpan = 0;
		}
	}
	
	
	Vector3 getDist(Vector3 posA, Vector3 posB){
		Vector3 distL = posA - posB;
		Vector3 distAbs = new Vector3( Mathf.Abs(distL.x), Mathf.Abs (distL.y), Mathf.Abs (distL.z));
		return distAbs;
	}
}
