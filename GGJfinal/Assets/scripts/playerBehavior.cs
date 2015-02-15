using UnityEngine;
using System.Collections;

public class playerBehavior : MonoBehaviour {



	 public float bound = 10.0f;
	[HideInInspector] public float velocity;
	[HideInInspector] public float mass;
	[HideInInspector] public float playerForce;
	[HideInInspector] public float velBound = 0.05f;
	private bool isTimer= false;
	
	float timer =0.0f;
	float timerMax = 20.0f;

	[HideInInspector] public int life;

	void Awake(){
		life = 5;
		tag = "player";
		playerForce = 1.0f;
		mass = 1.0f;
		transform.forward = new Vector3(0.0f, 0.1f, 0f);
		velocity = 0.01f;

	}
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
		transform.position += transform.forward*velocity;
		velocity += 0.0001f*playerForce;
		boundVelocity();
		boundRebounce ();
		if(isTimer == true) {
			Debug.Log ("Hello");
			timer += Time.deltaTime;
			Debug.Log ("deltaTime");
			if (timer >= timerMax) {
				// col trigger
				gameObject.collider.enabled = true;
				isTimer = false;
				Debug.Log ("updating");
			}
			
		}

		if ( life <= 0 ){
			Application.LoadLevel(2);
		}



	}

	void boundRebounce(){

		if( Mathf.Abs (transform.position.x) >= bound || Mathf.Abs (transform.position.y) >= bound ){
			transform.forward *= (-1f);
			playerForce *= 0.3f;
		}
	}

	public void isTrigger(GameObject passedItem){
		Destroy(passedItem);
		isTimer = true;
		
	}

	void boundVelocity(){
		if( velocity > velBound ){
			velocity = velBound;
		}
	}
}
