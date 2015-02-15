using UnityEngine;
using System.Collections;

public class planet : MonoBehaviour {

	private GameObject director;
	private GameObject player;
	public float massMax;
	public float mass;

	private float initialMass;

	public GameObject explosion;
	private Vector3 dist;

	private float range = 10.0f;
	private float lifeSpan;
	private float scaleAdjust = 0.03f;

	private bool isCreated;

	// Use this for initialization
	void Start () {
		director = GameObject.FindGameObjectWithTag ("Director");
		player = director.GetComponent<GameDirector>().player;
		dist = new Vector3 (1000000f, 10000000f, 0f);
	
		mass = Random.Range (0, massMax);
		initialMass = mass;

		transform.localScale = new Vector3(0, 0, 0);
		lifeSpan = 0;
		isCreated = false;

	}
	
	// Update is called once per frame
	void Update () {
	
		dist = getDist(transform.position, player.transform.position);
		drawPlayer ();
		colorUpdate ();
		lifeSpan += Time.deltaTime;
		growMass (0.5f);

		if ( lifeSpan >= 1.0f ){
			isCreated = true;
		}

		if( lifeSpan >= 5.0f ){
			if( Vector3.Magnitude(dist) >= range ){
				Destroy (gameObject);
			}else{
				lifeSpan = 0;
			}
		}

	
	}

	void drawPlayer(){

		float sampleDist = Vector3.Magnitude(dist);
		Vector3 drawingForce = mass*(transform.position - player.transform.position)/(sampleDist*sampleDist);
		Vector3 totalForce = player.transform.forward*player.GetComponent<playerBehavior>().playerForce + drawingForce;
		player.transform.forward = Vector3.Normalize(totalForce);
		player.GetComponent<playerBehavior>().playerForce = Vector3.Magnitude (totalForce);
	}

	Vector3 getDist(Vector3 posA, Vector3 posB){
		Vector3 distL = posA - posB;
		Vector3 distAbs = new Vector3( Mathf.Abs(distL.x), Mathf.Abs (distL.y), Mathf.Abs (distL.z));
		return distAbs;
	}

	void OnExplode(){
		// Create a quaternion with a random rotation in the z-axis.
		Quaternion randomRotation = Quaternion.Euler(0f, 0f, Random.Range(0f, 360f));
		// Instantiate the explosion where the rocket is with the random rotation.
		GameObject tmp = (GameObject) Instantiate(explosion, transform.position, randomRotation);
		Destroy (tmp, 3.0f);

	}

	void OnTriggerEnter(Collider col){
	//	Debug.Log (col.tag);
		if (col.tag == "player") {
						OnExplode ();
			player.GetComponent<playerBehavior>().life -= 1;
			Destroy(gameObject);
				}
		//	director.GetComponent<GameDirector>().gamePuase();
	}

	void colorUpdate(){
		gameObject.light.intensity = mass*1.0f;
		//renderer.material.color =  new Color(1.0f*mass, 0, 0);
	}

	public void increaseMass(){
		mass += 1.0f;
	}

	public void decreaseMass(){
		mass -= 1.0f;
	}

	void growMass(float timeInterval){
		if( lifeSpan/timeInterval <= 1 && isCreated == false){
			float newMass = (lifeSpan*initialMass/timeInterval)*scaleAdjust;
			transform.localScale = new Vector3 ( newMass, newMass, newMass);
		}
	}


}
