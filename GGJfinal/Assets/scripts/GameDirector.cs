using UnityEngine;
using System.Collections;

public class GameDirector : MonoBehaviour {

	[HideInInspector] public GameObject player;
	[HideInInspector] public GameObject [] planets;
	[HideInInspector] public GameObject UI_velocity;
	[HideInInspector] public GameObject[] wormholes;
	[HideInInspector] public GameObject [] obstacles;

	public int asteroidNum;
	public GameObject asteroidPrefab;
	private GameObject [] asteroids;


	// Use this for initialization
	void Awake () {
			
		player = GameObject.FindGameObjectWithTag("player");
		planets = GameObject.FindGameObjectsWithTag("planet");
		UI_velocity = GameObject.Find("UI_velocity");
		wormholes = GameObject.FindGameObjectsWithTag ("wormhole");
		obstacles = GameObject.FindGameObjectsWithTag ("obstacle");
		asteroids = new GameObject[asteroidNum];

		renderAsteroid();
	}
	
	// Update is called once per frame
	void Update () {

		uiControl ();
	}

	void uiControl(){
		float velBound = player.GetComponent<playerBehavior>().velBound;
		UI_velocity.transform.localScale = new Vector3 ( (player.GetComponent<playerBehavior>().velocity/velBound)*20,
		                                                UI_velocity.transform.localScale.y,
		                                                UI_velocity.transform.localScale.z);
	}

	void renderAsteroid(){
		float bound = player.GetComponent<playerBehavior>().bound;
		float x = 0.0f; 
		float y = 0.0f; 

		for( int i = 0; i < asteroidNum; i++ ){
			x = Random.Range(-bound, bound);
			y = Random.Range(-bound, bound);
			asteroids[i] = (GameObject) Instantiate(asteroidPrefab, new Vector3(x, y, 0.0f), transform.rotation);
		}
	}

	public void gamePuase(){
		Application.LoadLevel (2);
	}


}
