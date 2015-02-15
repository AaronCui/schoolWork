using UnityEngine;
using System.Collections;

public class item : MonoBehaviour {

	private GameObject player;
	private GameObject director;
	private float lifeSpan;

	// Use this for initialization
	void Start ()
	{
		director = GameObject.FindGameObjectWithTag ("Director");	
		player = director.GetComponent<GameDirector> ().player;
		lifeSpan = 0;	
	}
	
	// Update is called once per frame
	void Update ()
	{
		lifeSpan += Time.deltaTime;
		if (lifeSpan >= 5.0f ){
			killItself();
		}
		
	}
	
	void OnTriggerEnter(Collider col){
		if (col.gameObject.tag == "player") {
			col.gameObject.collider.enabled = false;
			Debug.Log ("inside if ");
			player.GetComponent<playerBehavior>().isTrigger(gameObject);
			//Destroy (gameObject);
		}
		//audio.Play ();
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
